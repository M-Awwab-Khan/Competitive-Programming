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
RUN_TIMEOUT ?= 5
export CP_NAME := $(NAME)
export CP_LANG := $(LANG)
export CP_SOURCE := $(SOURCE)
export CP_PCH := $(PCH)
export CP_RUN_TIMEOUT := $(RUN_TIMEOUT)
export CP_FILE :=
export CXX
export CPPFLAGS
export CXXFLAGS

# Make treats positional filenames as targets. Consume exactly one filename for
# problem commands, without a catch-all rule that would hide misspelled targets.
problem_actions := $(filter new build run check,$(MAKECMDGOALS))
ifneq ($(strip $(problem_actions)),)
ifneq ($(words $(problem_actions)),1)
$(error Use one problem command per invocation: make run problem.cpp)
endif
problem_files := $(filter-out $(problem_actions),$(MAKECMDGOALS))
ifneq ($(strip $(problem_files)),)
ifneq ($(words $(problem_files)),1)
$(error Supply exactly one filename: make new problem.cpp)
endif
ifeq ($(filter %.cpp %.py,$(problem_files)),)
$(error Expected a .cpp or .py filename: make new problem.cpp)
endif
export CP_FILE := $(problem_files)
.PHONY: $(problem_files)
$(problem_files):
	@:
endif
endif

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
