cmd_/home/nikita/CLionProjects/Lab2OS/modules.order := {   echo /home/nikita/CLionProjects/Lab2OS/dentry.ko;   echo /home/nikita/CLionProjects/Lab2OS/mult_sig.ko; :; } | awk '!x[$$0]++' - > /home/nikita/CLionProjects/Lab2OS/modules.order
