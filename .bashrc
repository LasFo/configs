#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

HISTSIZE=10000
HISTFILESIZE=10000
export PATH=~/bin:$PATH
export EDITOR=nvim

alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '
source $HOME/.config/bazel/bazel-complete.bash
