/*
 * cpumaxfreq.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cpufreq.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int cpumaxfreq_show(struct seq_file *m, void *v)
{
	struct cpufreq_policy *policy = NULL;
	unsigned int freq = 0;

	policy = cpufreq_cpu_get(7);
	freq = policy->cpuinfo.max_freq;

	if (freq > 2900000)
		seq_printf(m, "2.96\n");
	else
		seq_printf(m, "2.84\n");

	return 0;
}

static int cpumaxfreq_open(struct inode *inode, struct file *file)
{
	return single_open(file, &cpumaxfreq_show, NULL);
}

static const struct file_operations proc_cpumaxfreq_operations = {
	.open       = cpumaxfreq_open,
	.read       = seq_read,
	.llseek     = seq_lseek,
	.release    = seq_release,
};

static int __init proc_cpumaxfreq_init(void)
{
	proc_create("cpumaxfreq", 0, NULL, &proc_cpumaxfreq_operations);
	return 0;
}
fs_initcall(proc_cpumaxfreq_init);
