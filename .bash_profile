# colorful bash
export CLICOLOR=1
export LSCOLORS=GxFxCxDxBxegedabagaced

# show git branch name and status
GIT_PS1_SHOWUPSTREAM="auto"
GIT_PS1_SHOWCOLORHINTS="yes"
GIT_PS1_SHOWDIRTYSTATE="yes"
GIT_PS1_SHOWUNTRACKEDFILES="yes"
source ~/.git-prompt.sh
export PROMPT_COMMAND='__git_ps1 "\u@\h:\W" "\\\$ ";'
