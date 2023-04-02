#!/usr/bin/env bash
if [[ $DEBUG == true ]];then
PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]:+${FUNCNAME[0]}():} '
set -x
fi
configure=1
cd "$(dirname "$0")"||exit 1
while [[ $# -gt 0 ]];do
case "$1" in
-s)((configure--));;
*)configure_args+=("$1")
esac
shift
done
function writestr {
local color endchr inputcolor message nocolor runmessage
endchr='\n'
nocolor="\e[0m"
runmessage=0
while [[ $# -ne 0 ]];do
case "$1" in
-c)\
inputcolor="${2/grey/brightblack}"
[[ ${inputcolor#bright} ]]&&color='\e[1m'
case "${inputcolor#bright}" in
black)color+='\e[30m';;
red)color+='\e[31m';;
green)color+='\e[32m';;
yellow)color+='\e[33m';;
blue)color+='\e[34m';;
magenta)color+='\e[35m';;
cyan)color+='\e[36m';;
white)color+='\e[37m';;
*)color='\e[01m\e[31m'
esac
shift
;;
-e)runmessage=1;;
-n)endchr='';;
*)message+="$1"
esac
shift
done
printf "$color$message$nocolor$endchr"
if [[ $runmessage -ne 0 ]];then
eval "$message"
fi
}
set -e
{ {
writestr -n -c brightyellow 'Running: '
writestr -e -c brightwhite 'autoreconf --force --install --verbose'
}&&[[ $configure -ne 0 ]]&&{
printf '\n'
writestr -n -c brightyellow 'Running: '
writestr -e -c brightwhite "./configure ${configure_args[*]}"
};}
