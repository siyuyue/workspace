# Use git from homebrew
alias git='/usr/local/bin/git'

# colorful bash
export CLICOLOR=1
export LSCOLORS=GxFxCxDxBxegedabagaced
YELLOW="\e[93m"
CYAN="\e[96m"
RESET="\e[0m"

# show git branch name and status
GIT_PS1_SHOWUPSTREAM="auto"
GIT_PS1_SHOWCOLORHINTS="yes"
GIT_PS1_SHOWDIRTYSTATE="yes"
GIT_PS1_SHOWUNTRACKEDFILES="yes"
source ~/.git-prompt.sh
regex=".*\/([^\/]*)\/[^\/]*$"
export PROMPT_COMMAND='__git_ps1 "\[${YELLOW}\]${VIRTUAL_ENV:+$(echo $VIRTUAL_ENV | sed -E "s/$regex/(\1)/")}\[${RESET}\]\u@\h:\[${CYAN}\]\W\[${RESET}\]" "\\\$ ";'
