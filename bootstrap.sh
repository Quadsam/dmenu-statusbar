#!/usr/bin/env bash
cd "$(dirname "$0")"||exit 1
configure=1
while [[ $# -gt 0 ]];do
case "$1" in
-s|--skip-configure)((configure--));;
*)configure_args+=("$1")
esac
shift
done
function writestr {
local color endchr message nocolor runmessage
endchr='\n'
nocolor="$(tput sgr0)"
runmessage=0
while [[ $# -ne 0 ]];do
case "$1" in
-c)case "$2" in
black)color="$(tput setaf 0)";;
grey)color="$(tput bold)$(tput setaf 0)";;
red)color="$(tput setaf 1)";;
brightred)color="$(tput bold)$(tput setaf 1)";;
green)color="$(tput setaf 2)";;
brightgreen)color="$(tput bold)$(tput setaf 2)";;
yellow)color="$(tput setaf 3)";;
brightyellow)color="$(tput bold)$(tput setaf 3)";;
blue)color="$(tput setaf 4)";;
brightblue)color="$(tput bold)$(tput setaf 4)";;
magenta)color="$(tput setaf 5)";;
brightmagenta)color="$(tput bold)$(tput setaf 5)";;
cyan)color="$(tput setaf 6)";;
brightcyan)color="$(tput bold)$(tput setaf 6)";;
white)color="$(tput setaf 7)";;
brightwhite)color="$(tput bold)$(tput setaf 7)"
esac
shift 2
;;
-e)((runmessage++))
shift
;;
-n)\
endchr=''
shift
;;
*)\
message+="$1"
shift
esac
done
printf "$color$message$nocolor$endchr"
((runmessage))&&eval "$message"
}
writestr -n -c brightyellow 'Running: '
writestr -e -c brightwhite 'autoreconf --force --install --verbose'||exit 1
((configure))&&{
printf '\n'
writestr -n -c brightyellow 'Running: '
writestr -e -c brightwhite "./configure ${configure_args[*]}"||exit 1
}
