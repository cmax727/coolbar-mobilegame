##===============================================================
## Makefile リソース用
## $Id: Makefile 23:26 2009/09/10 stsokada $:
##===============================================================
SHELL = /bin/sh
.SUFFIXES:
.PHONY:

SOUND_DIR	= sound
SOUND_FILES	= $(shell find $(SOUND_DIR))
TOOL_DIR	= ../tool
TMP_DIR		= sound_tmp
OUT_DIR		= ../res

$(OUT_DIR)/*: $(SOUND_FILES)
	echo Test
