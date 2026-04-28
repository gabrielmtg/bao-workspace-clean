
all:
	@echo make what?

vms:
	@./scripts/util/build_vm.sh all

bao:
	@./scripts/util/build_bao.sh

copy:
	@./scripts/util/copy_files.sh

clean:
	@./scripts/util/clean.sh
