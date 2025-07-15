#!/usr/bin/env sh
deps="
bat
build-base
coreutils
curl
exa
git
htop
neovim
neovim-doc
openssh
openssl
ripgrep
shadow
tmux
wget
zsh
python3-dev
python3
py3-pip
linux-headers
autoconf
automake
libtool
m4
"
deps=$(printf "$deps" | tr '\n' ' ' | sed -e 's/^[[:space:]]*//')

apk add --no-cache $deps
