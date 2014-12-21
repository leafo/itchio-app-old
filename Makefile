
.PHONY: format

format:
	astyle -n --style=1tbs $$(git ls-files | grep cpp$$)