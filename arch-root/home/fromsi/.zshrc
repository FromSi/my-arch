export ZSH="/home/fromsi/.oh-my-zsh"

ZSH_THEME="bullet-train"

plugins=(git)

source $ZSH/oh-my-zsh.sh

BULLETTRAIN_TIME_12HR=true

BULLETTRAIN_PROMPT_ORDER=(
  time
  dir
  git
)

