#!/bin/bash

function chtag()
{
    tagname=$1
    export PROMPT_COMMAND='echo -ne "\033]0;$tagname\007"'
}

chtag $@
