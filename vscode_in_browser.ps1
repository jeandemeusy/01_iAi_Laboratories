param(
    [string]$dir,
    [string]$ip='127.0.0.1:8080',
    [switch]$h = $false
)

if($h) {
    Write-Host "Options :"
    Write-Host "`t -dir <path\to\dir> : sets the directory to share files from"
    Write-Host "`t -ip <IP> : sets the IP on which the container run"
    Write-Host "`t -h : displays this."

    exit
}


if(!($dir)) {
    Write-Host "Please specify a local directory ! "
    Write-Host "See '$((Get-Item $PSCommandPath ).Basename) -h'."

    exit
}

if(!(test-path $dir'\bin')) {
    Write-Host "Creating folder" $dir'\bin' -ForegroundColor DarkYellow
    md $dir'\bin' | out-null
}

Write-Host "Starting VS Code with ip" $ip "..." -ForegroundColor DarkGreen

start "http://$ip/?folder=/home/coder/project"
docker run -it -p $ip':8080' -v $dir'\bin:/home/coder/.local/share/code-server' -v $dir':/home/coder/project' 314rch/info:latest