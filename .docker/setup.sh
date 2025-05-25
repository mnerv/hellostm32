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
echo "export SHELL=$(which zsh)" >> ~/.zshrc
echo "export EDITOR=nvim" >> ~/.zshrc
echo "alias ls=exa" >> ~/.zshrc
echo "alias cat='bat -pp'" >> ~/.zshrc

