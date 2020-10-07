#include "image_filtering.h"

int main(int argc, char* argv[]) {
    option_type opt = read_arguments(argc, argv);

	// loading of the input image
	int width, height;
	uint8_t* src = imread(opt.input_filename, &width, &height);
	uint8_t* dst = NULL;
	if (!src) {
		log_err("Error while loading the image");
		exit(EXIT_FAILURE);
	}

	// application of filter
	if (opt.resize)
		resize(&src, &width, &height, opt.resize);

	switch(opt.type) {
		case EDGE:
			dst = edge(src, width, height);
			break;
		case SHARPEN:
		case BLUR:
		case V_EDGE:
		case H_EDGE:
			dst = filter(src, width, height, opt.type, opt.filter_size);
			break;
		case NO_OPERATION:
			dst = (uint8_t*)malloc(width*height*sizeof(uint8_t));
			memcpy(dst,src,width*height*sizeof(uint8_t));
			break;
		default:
			break;
	}

	// adjustments of contrasts
	if (opt.adjust)
		adjust_constrast(dst, width, height);

	// generation of output image
	if (dst) {
		imsave(dst, opt.output_filename, width, height);
		free(dst);
	}

	free(src);

	return 0;
}


// 2d operations
void conv_2d(uint8_t* src, uint8_t* dst, size_t src_w, size_t src_h, float* f, size_t f_w) {
	if (!(f_w & 1) || !(f_w > 1)) {
		log_err("Filtre size must be odd, and bigger than 1");
		return;
	}

	int src_off = f_w >> 1;
	for (int l = src_off; l < src_h-src_off; l++) {
		for (int c = src_off; c < src_w-src_off; c++) {
			double cumsum = 0;
			for (int f_l = -src_off; f_l <= src_off; f_l++) {
				for (int f_c = -src_off; f_c <= src_off; f_c++) {
					uint8_t img_data = get_pixel_uint8(src, src_w, c + f_c, l + f_l);
					float f_data = get_pixel_float(f, f_w, f_c + src_off, f_l + src_off);
					cumsum += img_data * f_data;
				}
			}

			set_pixel(dst, src_w, c, l, (uint8_t)(cumsum));
		}
	}
}

void get_filter_kernel(float** f, size_t size, operation type) {
	static float v_edge[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	static float h_edge[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	static float sharpen[] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };
	static float blur[] = { 1./16, 1./8, 1./16, 1./8, 1./4, 1./8, 1./16, 1./8, 1./16 };

	*f = (float*)malloc(size * size* sizeof(int8_t*));

	switch(type) {
		case V_EDGE:
			memcpy(*f, v_edge, sizeof(v_edge));
			break;
		case H_EDGE:
			memcpy(*f, h_edge, sizeof(h_edge));
			break;
		case SHARPEN:
			memcpy(*f, sharpen, sizeof(sharpen));
			break;
		case BLUR:
			memcpy(*f, blur, sizeof(blur));
			break;
		default:
			break;
	}

}

uint8_t* edge(uint8_t* src, size_t src_w, size_t src_h) {
	uint8_t* dst_h = filter(src, src_w, src_h, H_EDGE, 3);
	uint8_t* dst_v = filter(src, src_w, src_h, V_EDGE, 3);
	uint8_t* dst = (uint8_t*)calloc(src_w * src_h, sizeof(uint8_t*));

	for(int l = 0; l < src_h; l++) {
		for(int c = 0; c < src_w; c++) {
			uint16_t val_h = get_pixel_uint8(dst_h,src_w,c,l);
			uint16_t val_v = get_pixel_uint8(dst_v,src_w,c,l);
			
			set_pixel(dst, src_w, c, l, (uint8_t)SQRT(val_h, val_v));
		}
	}

	free(dst_h);
	free(dst_v);

	return dst;
}

void adjust_constrast(uint8_t* src, size_t src_w, size_t src_h) {
	int src_min = (int)get_min(src, src_w, src_h);
	int src_max = (int)get_max(src, src_w, src_h);
	float dst_min = 0., dst_max = 255.;

	for (int k = 0; k < src_w * src_h; k++)
		*(src + k) = (*(src+k) - src_min) * (dst_max - dst_min) / (src_max - src_min) + dst_min;
}

void resize(uint8_t** src, int* src_w, int* src_h, char* arg) {
	char* data = arg;
	do {
		if (*data++ == 'x') break;
	} while(data - arg < strlen(arg));

	float ratio_h, ratio_w;
	if (data-arg == strlen(arg)) {
		ratio_h = atof(arg);
		ratio_w = atof(arg);
	}
	else {
		char* h_substr = (char*)malloc((data-arg-1)*sizeof(char));
		char* w_substr = (char*)malloc(strlen(arg)-(data-arg)*sizeof(char));
		sprintf(h_substr,"%.*s", data-arg-1, arg);
		sprintf(w_substr,"%.*s", strlen(arg)-(data-arg), arg+(data-arg));
		ratio_h = 1.*atoi(h_substr) / *src_h;
		ratio_w = 1.*atoi(w_substr) / *src_w;
	}
	int dst_w = (*src_w*ratio_w);
	int dst_h = (*src_h*ratio_h);

	uint8_t* dst = (uint8_t*)malloc(dst_w*dst_h*sizeof(uint8_t));

	for (int l = 0; l < dst_h; l++) {
		for (int c = 0; c < dst_w; c++) {
			uint8_t val = 0;
			if ((int)(c/ratio_w) < *src_w && (int)(l/ratio_h) < *src_h)
				val = get_pixel_uint8(*src,*src_w,c/ratio_w,l/ratio_h);
			set_pixel(dst,dst_w,c,l,val);
		}
	}

	*src = (uint8_t*)realloc(*src,dst_w*dst_h*sizeof(uint8_t));
	memcpy(*src, dst, dst_w*dst_h* sizeof(uint8_t));
	free(dst);
	*src_w = dst_w;
	*src_h = dst_h;
}


// wrapper
uint8_t* filter(uint8_t* src, size_t src_w, size_t src_h, operation type, size_t size) {
	float *f;
	uint8_t* dst = (uint8_t*)calloc(src_w * src_h, sizeof(uint8_t*));

	get_filter_kernel(&f, size, type);
	conv_2d(src, dst, src_w, src_h, f, size);

	free(f);

	return dst;
}

uint8_t* imread(char* filename, int* width, int* height) {
	return stbi_load(filename, width, height, NULL, 1);
}

void imsave(uint8_t* img, char* filename, int width, int height) {
	stbi_write_png(filename, width, height, 1, img, width);
}


// setter-getter
uint8_t get_pixel_uint8(uint8_t* src, size_t width, size_t x, size_t y) {
	return *(src + (x + width * y));
}
float get_pixel_float(float* src, size_t width, size_t x, size_t y) {
	return *(src + (x + width * y));
}
void set_pixel(uint8_t* src, size_t width, size_t x, size_t y, uint8_t val) {
	*(src + (x + width * y)) = val;
}

uint8_t get_min(uint8_t* src, size_t src_w, size_t src_h) {
	uint8_t min_val = UINT8_MAX;

	for (int k = 0; k < src_w * src_h; k++)
		min_val = MIN(*(src+k), min_val);

	return min_val;
}

uint8_t get_max(uint8_t* src, size_t src_w, size_t src_h) {
	uint8_t max_val = 0;

	for (int k = 0; k < src_w * src_h; k++)
		max_val = MAX(*(src+k), max_val);

	return max_val;
}