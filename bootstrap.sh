#!/usr/bin/env bash
if [[ $DEBUG == true ]];then
PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]:+${FUNCNAME[0]}():} '
set -x
fi
configure=1
cd "$(dirname "$0")"||exit 1
eval set -- "$(getopt -n "$(basename "$0")" -- 'hs' "$@")"
while true;do
case $1 in
-h)cat <<EOF
Usage:
  $(basename "$0") [-h] [-s]

Options:
  -h  Show this help and exit.
  -s  Generate configure script but dont run it.
EOF
exit 0
;;
-s)((configure--))
shift
;;
--)shift
break
esac
done
function writestr {
local color endchr inputcolor nocolor runmessage
endchr='\n'
nocolor="\e[0m"
runmessage=0
eval set -- "$(getopt -n writestr -- 'c:en' "$@")"
while true;do
case $1 in
-c)inputcolor="${2/grey/brightblack}"
[[ ${inputcolor#bright} ]]&&color='\e[1m'
case "${inputcolor#bright}" in
black)color+='\e[30m'
;;
red)color+='\e[31m'
;;
green)color+='\e[32m'
;;
yellow)color+='\e[33m'
;;
blue)color+='\e[34m'
;;
magenta)color+='\e[35m'
;;
cyan)color+='\e[36m'
;;
white)color+='\e[37m'
;;
*)color='\e[01m\e[31m'
esac
shift 2
;;
-e)runmessage=1
shift
;;
-n)endchr=''
shift
;;
--)shift
break
esac
done
printf "$color$*$nocolor$endchr"
if [[ $runmessage -ne 0 ]];then
eval "$*"
fi
}
set -e
{
{
writestr -n -c brightyellow 'Running: '
writestr -e -c brightwhite 'autoreconf --force --install --verbose'
}&&[[ $configure -ne 0 ]]&&{
printf '\n'
writestr -n -c brightyellow 'Running: '
writestr -e -c brightwhite "./configure $*"
}
}
