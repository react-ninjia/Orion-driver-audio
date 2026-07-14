#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};


MODULE_INFO(depends, "snd-soc-core");

MODULE_ALIAS("acpi*:RTL5682:*");
MODULE_ALIAS("acpi*:MX98357:*");

MODULE_INFO(srcversion, "783B3CA6405B97781B918DB");
