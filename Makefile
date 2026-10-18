.DEFAULT_GOAL := help
PYTHON ?= python3
NAME ?=
LANG ?= cpp
# LANG is normally a locale inherited from the shell, not a language choice.
ifeq ($(origin LANG),environment)
LANG := cpp
endif
SOURCE ?=
PCH ?= 1
export CP_NAME := $(NAME)
export CP_LANG := $(LANG)
export CP_SOURCE := $(SOURCE)
export CP_PCH := $(PCH)
export CXX
export CPPFLAGS
export CXXFLAGS

.PHONY: help new build run check pch ingest ingest-apply lint
help:
	@$(PYTHON) scripts/problem.py help
new build run check pch:
	@$(PYTHON) scripts/problem.py $@
ingest:
	@$(PYTHON) scripts/ingest.py
ingest-apply:
	@$(PYTHON) scripts/ingest.py --apply
lint:
	@$(PYTHON) scripts/lint_repo.py
