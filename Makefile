TARGET    = itchio
BUILD_DIR = build

.PHONY: client run format clean help

client: $(BUILD_DIR)/Makefile
	@make -C $(BUILD_DIR)

run: client
	@$(BUILD_DIR)/$(TARGET)

format:
	astyle -n --style=1tbs $$(git ls-files | grep cpp$$)

clean:
	@rm -rf $(BUILD_DIR)

help:
	@echo "Available targets:"
	@echo "  client    Build the itch.io client."
	@echo "  run       Build and execute the itch.io client."
	@echo "  format    Format the project's codebase."
	@echo "  clean     Delete built project files."
	@echo "  help      Print this help page."
	@echo

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/Makefile: $(BUILD_DIR)
	@qmake -Wall $(TARGET).pro -o $@
