#!/usr/bin/env sh

BASEDIR="$(readlink -f $(dirname $0))"

# Setup nvim
mkdir -p ~/.config/nvim
cp -r .docker/mini.lua ~/.config/nvim/init.lua

# git configuration
git config --global --add safe.directory /app
git config --global core.autocrlf false

# Change default shell to zsh
echo "" | chsh -s $(which zsh)

# zsh config
cat << EOF > ~/.zshrc
export SHELL="\$(which zsh)"

export EDITOR="nvim"
export VISUAL="\$EDITOR"

alias vim=nvim
alias vi=nvim
alias edit=nvim

alias ls="exa"
alias cat="bat -pp"

# Alias cd to to dot shortcuts
alias ..='cd ..'
alias ...='cd ../..'
alias ....='cd ../../..'
alias .....='cd ../../../..'
alias ......='cd ../../../../..'

# Define what is a word use for jumping around
WORDCHARS='*?_-.[]~=&;#$%^(){}<>/ '$'\n'

# Keybindings
bindkey "^[[1;3C" forward-word
bindkey "^[[1;3D" backward-word
bindkey "^[[1;5C" forward-word
bindkey "^[[1;5D" backward-word
EOF
