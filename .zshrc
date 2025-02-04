export ZSH="$HOME/.oh-my-zsh"

ZSH_THEME="arrows"

zstyle ':omz:update' mode disabled 

ENABLE_CORRECTION="true"

plugins=(git)

source $ZSH/oh-my-zsh.sh

fortune -s
echo
