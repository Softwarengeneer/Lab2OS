#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
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

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xeeab4c1e, "module_layout" },
	{ 0x750758b6, "debugfs_remove" },
	{ 0x999e8297, "vfree" },
	{ 0xfc1590c7, "debugfs_create_file" },
	{ 0x356e31cc, "debugfs_create_blob" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x836316f6, "get_pid_task" },
	{ 0x98c8bd71, "find_get_pid" },
	{ 0x381bd18c, "debugfs_create_dir" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7B14EF5C8A3E1BFE7D940E7");
