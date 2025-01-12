/* SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause) */

/* THIS FILE IS AUTOGENERATED BY BPFTOOL! */
#ifndef __MINIMAL_BPF_SKEL_H__
#define __MINIMAL_BPF_SKEL_H__

#include <errno.h>
#include <stdlib.h>
#include <bpf/libbpf.h>

struct minimal_bpf {
	struct bpf_object_skeleton *skeleton;
	struct bpf_object *obj;
	struct {
		struct bpf_map *rodata;
	} maps;
	struct {
		struct bpf_program *handle_tp;
	} progs;
	struct {
		struct bpf_link *handle_tp;
	} links;

#ifdef __cplusplus
	static inline struct minimal_bpf *open(const struct bpf_object_open_opts *opts = nullptr);
	static inline struct minimal_bpf *open_and_load();
	static inline int load(struct minimal_bpf *skel);//open load attach detach destroy elf_bytes
	static inline int attach(struct minimal_bpf *skel);
	static inline void detach(struct minimal_bpf *skel);
	static inline void destroy(struct minimal_bpf *skel);
	static inline const void *elf_bytes(size_t *sz);
#endif /* __cplusplus */
};

static void
minimal_bpf__destroy(struct minimal_bpf *obj)
{
	if (!obj)
		return;
	if (obj->skeleton)
		bpf_object__destroy_skeleton(obj->skeleton);
	free(obj);
}

static inline int
minimal_bpf__create_skeleton(struct minimal_bpf *obj);

static inline struct minimal_bpf *
minimal_bpf__open_opts(const struct bpf_object_open_opts *opts)
{
	struct minimal_bpf *obj;
	int err;

	obj = (struct minimal_bpf *)calloc(1, sizeof(*obj));
	if (!obj) {
		errno = ENOMEM;
		return NULL;
	}

	err = minimal_bpf__create_skeleton(obj);
	if (err)
		goto err_out;

	err = bpf_object__open_skeleton(obj->skeleton, opts);
	if (err)
		goto err_out;

	return obj;
err_out:
	minimal_bpf__destroy(obj);
	errno = -err;
	return NULL;
}

static inline struct minimal_bpf *
minimal_bpf__open(void)
{
	return minimal_bpf__open_opts(NULL);
}

static inline int
minimal_bpf__load(struct minimal_bpf *obj)
{
	return bpf_object__load_skeleton(obj->skeleton);
}

static inline struct minimal_bpf *
minimal_bpf__open_and_load(void)
{
	struct minimal_bpf *obj;
	int err;

	obj = minimal_bpf__open();
	if (!obj)
		return NULL;
	err = minimal_bpf__load(obj);
	if (err) {
		minimal_bpf__destroy(obj);
		errno = -err;
		return NULL;
	}
	return obj;
}

static inline int
minimal_bpf__attach(struct minimal_bpf *obj)
{
	return bpf_object__attach_skeleton(obj->skeleton);
}

static inline void
minimal_bpf__detach(struct minimal_bpf *obj)
{
	bpf_object__detach_skeleton(obj->skeleton);
}

static inline const void *minimal_bpf__elf_bytes(size_t *sz);

static inline int
minimal_bpf__create_skeleton(struct minimal_bpf *obj)
{
	struct bpf_object_skeleton *s;
	int err;

	s = (struct bpf_object_skeleton *)calloc(1, sizeof(*s));
	if (!s)	{
		err = -ENOMEM;
		goto err;
	}

	s->sz = sizeof(*s);
	s->name = "minimal_bpf";
	s->obj = &obj->obj;

	/* maps */
	s->map_cnt = 1;
	s->map_skel_sz = sizeof(*s->maps);
	s->maps = (struct bpf_map_skeleton *)calloc(s->map_cnt, s->map_skel_sz);
	if (!s->maps) {
		err = -ENOMEM;
		goto err;
	}

	s->maps[0].name = "minimal_.rodata";
	s->maps[0].map = &obj->maps.rodata;

	/* programs */
	s->prog_cnt = 1;
	s->prog_skel_sz = sizeof(*s->progs);
	s->progs = (struct bpf_prog_skeleton *)calloc(s->prog_cnt, s->prog_skel_sz);
	if (!s->progs) {
		err = -ENOMEM;
		goto err;
	}

	s->progs[0].name = "handle_tp";
	s->progs[0].prog = &obj->progs.handle_tp;
	s->progs[0].link = &obj->links.handle_tp;

	s->data = minimal_bpf__elf_bytes(&s->data_sz);

	obj->skeleton = s;
	return 0;
err:
	bpf_object__destroy_skeleton(s);
	return err;
}

static inline const void *minimal_bpf__elf_bytes(size_t *sz)
{
	static const char data[] __attribute__((__aligned__(8))) = "\
\x7f\x45\x4c\x46\x02\x01\x01\0\0\0\0\0\0\0\0\0\x01\0\xf7\0\x01\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\x78\x0d\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\0\x40\0\x1b\0\
\x01\0\x85\0\0\0\x0e\0\0\0\x77\0\0\0\x20\0\0\0\x18\x01\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\xb7\x02\0\0\x1c\0\0\0\xbf\x03\0\0\0\0\0\0\x85\0\0\0\x06\0\0\0\xb7\0\0\0\0\
\0\0\0\x95\0\0\0\0\0\0\0\x47\x50\x4c\0\x42\x50\x46\x20\x74\x72\x69\x67\x67\x65\
\x72\x65\x64\x20\x66\x72\x6f\x6d\x20\x50\x49\x44\x20\x25\x64\x2e\x0a\0\x12\0\0\
\0\x05\0\x08\0\x01\0\0\0\x04\0\0\0\x04\x08\x10\x01\x50\0\x01\x11\x01\x25\x25\
\x13\x05\x03\x25\x72\x17\x10\x17\x1b\x25\x11\x1b\x12\x06\x73\x17\x8c\x01\x17\0\
\0\x02\x34\0\x03\x25\x49\x13\x3f\x19\x3a\x0b\x3b\x0b\x02\x18\0\0\x03\x01\x01\
\x49\x13\0\0\x04\x21\0\x49\x13\x37\x0b\0\0\x05\x24\0\x03\x25\x3e\x0b\x0b\x0b\0\
\0\x06\x24\0\x03\x25\x0b\x0b\x3e\x0b\0\0\x07\x34\0\x03\x25\x49\x13\x3a\x0b\x3b\
\x05\0\0\x08\x26\0\x49\x13\0\0\x09\x0f\0\x49\x13\0\0\x0a\x15\0\x49\x13\x27\x19\
\0\0\x0b\x16\0\x49\x13\x03\x25\x3a\x0b\x3b\x0b\0\0\x0c\x2e\x01\x11\x1b\x12\x06\
\x40\x18\x7a\x19\x03\x25\x3a\x0b\x3b\x0b\x27\x19\x49\x13\x3f\x19\0\0\x0d\x34\0\
\x03\x25\x49\x13\x3a\x0b\x3b\x0b\x02\x18\0\0\x0e\x05\0\x03\x25\x3a\x0b\x3b\x0b\
\x49\x13\0\0\x0f\x34\0\x02\x22\x03\x25\x3a\x0b\x3b\x0b\x49\x13\0\0\x10\x34\0\
\x03\x25\x49\x13\x3a\x0b\x3b\x0b\0\0\x11\x15\x01\x49\x13\x27\x19\0\0\x12\x05\0\
\x49\x13\0\0\x13\x18\0\0\0\x14\x0f\0\0\0\0\xe1\0\0\0\x05\0\x01\x08\0\0\0\0\x01\
\0\x1d\0\x01\x08\0\0\0\0\0\0\0\x02\x02\x48\0\0\0\x08\0\0\0\x0c\0\0\0\x02\x03\
\x32\0\0\0\0\x04\x02\xa1\0\x03\x3e\0\0\0\x04\x42\0\0\0\x04\0\x05\x04\x06\x01\
\x06\x05\x08\x07\x07\x06\x4f\0\0\0\x02\x72\x01\x08\x54\0\0\0\x09\x59\0\0\0\x0a\
\x5e\0\0\0\x0b\x66\0\0\0\x08\x01\x1f\x05\x07\x07\x08\x0c\x02\x48\0\0\0\x01\x5a\
\x0e\0\x07\xdf\0\0\0\x0d\x09\x96\0\0\0\0\x0a\x02\xa1\x01\x0e\x11\0\x07\xe3\0\0\
\0\x0f\0\x10\0\x09\xdf\0\0\0\0\x03\xa2\0\0\0\x04\x42\0\0\0\x1c\0\x08\x3e\0\0\0\
\x10\x0a\xaf\0\0\0\x02\xb1\x08\xb4\0\0\0\x09\xb9\0\0\0\x11\xca\0\0\0\x12\xce\0\
\0\0\x12\xd3\0\0\0\x13\0\x05\x0b\x05\x08\x09\xa2\0\0\0\x0b\xdb\0\0\0\x0d\x01\
\x1b\x05\x0c\x07\x04\x05\x0f\x05\x04\x14\0\x4c\0\0\0\x05\0\0\0\0\0\0\0\x15\0\0\
\0\x23\0\0\0\x4e\0\0\0\x56\0\0\0\x5b\0\0\0\x6f\0\0\0\x88\0\0\0\x9b\0\0\0\xa1\0\
\0\0\xa9\0\0\0\xba\0\0\0\xbf\0\0\0\xcc\0\0\0\xd2\0\0\0\xdc\0\0\0\xe0\0\0\0\xe4\
\0\0\0\x63\x6c\x61\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x31\x38\x2e\x31\
\x2e\x38\0\x6d\x69\x6e\x69\x6d\x61\x6c\x2e\x62\x70\x66\x2e\x63\0\x2f\x68\x6f\
\x6d\x65\x2f\x79\x6c\x78\x2f\xe6\x88\x91\xe7\x9a\x84\xe9\xa1\xb9\xe7\x9b\xae\
\x2f\x77\x6c\x78\x2d\x64\x6d\x2f\x65\x62\x70\x66\x2f\x6c\x69\x62\x62\x70\x66\
\x63\0\x4c\x49\x43\x45\x4e\x53\x45\0\x63\x68\x61\x72\0\x5f\x5f\x41\x52\x52\x41\
\x59\x5f\x53\x49\x5a\x45\x5f\x54\x59\x50\x45\x5f\x5f\0\x62\x70\x66\x5f\x67\x65\
\x74\x5f\x63\x75\x72\x72\x65\x6e\x74\x5f\x70\x69\x64\x5f\x74\x67\x69\x64\0\x75\
\x6e\x73\x69\x67\x6e\x65\x64\x20\x6c\x6f\x6e\x67\x20\x6c\x6f\x6e\x67\0\x5f\x5f\
\x75\x36\x34\0\x5f\x5f\x5f\x5f\x66\x6d\x74\0\x62\x70\x66\x5f\x74\x72\x61\x63\
\x65\x5f\x70\x72\x69\x6e\x74\x6b\0\x6c\x6f\x6e\x67\0\x75\x6e\x73\x69\x67\x6e\
\x65\x64\x20\x69\x6e\x74\0\x5f\x5f\x75\x33\x32\0\x68\x61\x6e\x64\x6c\x65\x5f\
\x74\x70\0\x69\x6e\x74\0\x70\x69\x64\0\x63\x74\x78\0\x1c\0\0\0\x05\0\x08\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x9f\xeb\x01\0\x18\0\0\0\0\0\
\0\0\xe8\0\0\0\xe8\0\0\0\x6d\x01\0\0\0\0\0\0\0\0\0\x02\0\0\0\0\0\0\0\0\x01\0\0\
\x0d\x03\0\0\0\x01\0\0\0\x01\0\0\0\x05\0\0\0\0\0\0\x01\x04\0\0\0\x20\0\0\x01\
\x09\0\0\0\x01\0\0\x0c\x02\0\0\0\x2a\x01\0\0\0\0\0\x01\x01\0\0\0\x08\0\0\x01\0\
\0\0\0\0\0\0\x03\0\0\0\0\x05\0\0\0\x07\0\0\0\x04\0\0\0\x2f\x01\0\0\0\0\0\x01\
\x04\0\0\0\x20\0\0\0\x43\x01\0\0\0\0\0\x0e\x06\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\
\x0a\x05\0\0\0\0\0\0\0\0\0\0\x03\0\0\0\0\x09\0\0\0\x07\0\0\0\x1c\0\0\0\x4b\x01\
\0\0\0\0\0\x0e\x0a\0\0\0\0\0\0\0\x5d\x01\0\0\x01\0\0\x0f\0\0\0\0\x0b\0\0\0\0\0\
\0\0\x1c\0\0\0\x65\x01\0\0\x01\0\0\x0f\0\0\0\0\x08\0\0\0\0\0\0\0\x04\0\0\0\0\
\x63\x74\x78\0\x69\x6e\x74\0\x68\x61\x6e\x64\x6c\x65\x5f\x74\x70\0\x74\x72\x61\
\x63\x65\x70\x6f\x69\x6e\x74\x2f\x73\x79\x73\x63\x61\x6c\x6c\x73\x2f\x73\x79\
\x73\x5f\x65\x6e\x74\x65\x72\x5f\x77\x72\x69\x74\x65\0\x2f\x68\x6f\x6d\x65\x2f\
\x79\x6c\x78\x2f\xe6\x88\x91\xe7\x9a\x84\xe9\xa1\xb9\xe7\x9b\xae\x2f\x77\x6c\
\x78\x2d\x64\x6d\x2f\x65\x62\x70\x66\x2f\x6c\x69\x62\x62\x70\x66\x63\x2f\x6d\
\x69\x6e\x69\x6d\x61\x6c\x2e\x62\x70\x66\x2e\x63\0\x20\x20\x20\x20\x20\x20\x20\
\x20\x69\x6e\x74\x20\x70\x69\x64\x20\x3d\x20\x62\x70\x66\x5f\x67\x65\x74\x5f\
\x63\x75\x72\x72\x65\x6e\x74\x5f\x70\x69\x64\x5f\x74\x67\x69\x64\x28\x29\x20\
\x3e\x3e\x20\x33\x32\x3b\0\x20\x20\x20\x20\x20\x20\x20\x20\x62\x70\x66\x5f\x70\
\x72\x69\x6e\x74\x6b\x28\x22\x42\x50\x46\x20\x74\x72\x69\x67\x67\x65\x72\x65\
\x64\x20\x66\x72\x6f\x6d\x20\x50\x49\x44\x20\x25\x64\x2e\x5c\x6e\x22\x2c\x20\
\x70\x69\x64\x29\x3b\x20\x2f\x2f\xe5\x8f\xaf\x63\x61\x74\x20\x2f\x73\x79\x73\
\x2f\x6b\x65\x72\x6e\x65\x6c\x2f\x64\x65\x62\x75\x67\x2f\x74\x72\x61\x63\x69\
\x6e\x67\x2f\x74\x72\x61\x63\x65\xe6\x9f\xa5\xe7\x9c\x8b\xe8\xb0\x83\xe8\xaf\
\x95\xe4\xbf\xa1\xe6\x81\xaf\0\x20\x20\x20\x20\x20\x20\x20\x20\x72\x65\x74\x75\
\x72\x6e\x20\x30\x3b\0\x63\x68\x61\x72\0\x5f\x5f\x41\x52\x52\x41\x59\x5f\x53\
\x49\x5a\x45\x5f\x54\x59\x50\x45\x5f\x5f\0\x4c\x49\x43\x45\x4e\x53\x45\0\x68\
\x61\x6e\x64\x6c\x65\x5f\x74\x70\x2e\x5f\x5f\x5f\x5f\x66\x6d\x74\0\x2e\x72\x6f\
\x64\x61\x74\x61\0\x6c\x69\x63\x65\x6e\x73\x65\0\0\0\0\x9f\xeb\x01\0\x20\0\0\0\
\0\0\0\0\x14\0\0\0\x14\0\0\0\x4c\0\0\0\x60\0\0\0\0\0\0\0\x08\0\0\0\x13\0\0\0\
\x01\0\0\0\0\0\0\0\x04\0\0\0\x10\0\0\0\x13\0\0\0\x04\0\0\0\0\0\0\0\x37\0\0\0\
\x70\0\0\0\x13\x24\0\0\x08\0\0\0\x37\0\0\0\x70\0\0\0\x2e\x24\0\0\x10\0\0\0\x37\
\0\0\0\xa4\0\0\0\x09\x28\0\0\x38\0\0\0\x37\0\0\0\x18\x01\0\0\x09\x2c\0\0\0\0\0\
\0\x0c\0\0\0\xff\xff\xff\xff\x04\0\x08\0\x08\x7c\x0b\0\x14\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\x48\0\0\0\0\0\0\0\x90\0\0\0\x05\0\x08\0\x69\0\0\0\x08\x01\x01\xfb\
\x0e\x0d\0\x01\x01\x01\x01\0\0\0\x01\0\0\x01\x01\x01\x1f\x03\0\0\0\0\x2b\0\0\0\
\x44\0\0\0\x03\x01\x1f\x02\x0f\x05\x1e\x03\x55\0\0\0\0\x1e\xa2\xd3\0\x4c\xf9\
\x04\xba\x32\xc3\xbc\x75\x3e\x85\x96\xb8\x63\0\0\0\x01\xb8\x10\xf2\x70\x73\x3e\
\x10\x63\x19\xb6\x7e\xf5\x12\xc6\x24\x6e\x6e\0\0\0\x02\x65\xe4\xdc\x8e\x31\x21\
\xf9\x1a\x5c\x2c\x9e\xb8\x56\x3c\x56\x92\x04\0\x05\x13\x0a\0\x09\x02\0\0\0\0\0\
\0\0\0\x1a\x05\x2e\x06\x20\x05\x09\x06\x21\x59\x02\x02\0\x01\x01\x2f\x68\x6f\
\x6d\x65\x2f\x79\x6c\x78\x2f\xe6\x88\x91\xe7\x9a\x84\xe9\xa1\xb9\xe7\x9b\xae\
\x2f\x77\x6c\x78\x2d\x64\x6d\x2f\x65\x62\x70\x66\x2f\x6c\x69\x62\x62\x70\x66\
\x63\0\x2f\x75\x73\x72\x2f\x69\x6e\x63\x6c\x75\x64\x65\x2f\x61\x73\x6d\x2d\x67\
\x65\x6e\x65\x72\x69\x63\0\x2f\x75\x73\x72\x2f\x69\x6e\x63\x6c\x75\x64\x65\x2f\
\x62\x70\x66\0\x6d\x69\x6e\x69\x6d\x61\x6c\x2e\x62\x70\x66\x2e\x63\0\x69\x6e\
\x74\x2d\x6c\x6c\x36\x34\x2e\x68\0\x62\x70\x66\x5f\x68\x65\x6c\x70\x65\x72\x5f\
\x64\x65\x66\x73\x2e\x68\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\xff\0\0\0\x04\0\xf1\xff\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x03\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x22\0\0\0\x01\0\x06\0\0\0\0\0\0\0\0\0\x1c\0\
\0\0\0\0\0\0\0\0\0\0\x03\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\
\x07\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x08\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x03\0\x0b\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\
\x0d\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x0e\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x03\0\x14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\
\x16\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x18\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x86\0\0\0\x12\0\x03\0\0\0\0\0\0\0\0\0\x48\0\0\0\0\0\0\0\x2e\x01\0\
\0\x11\0\x05\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x01\0\0\0\
\x04\0\0\0\x08\0\0\0\0\0\0\0\x03\0\0\0\x06\0\0\0\x11\0\0\0\0\0\0\0\x03\0\0\0\
\x07\0\0\0\x15\0\0\0\0\0\0\0\x03\0\0\0\x0b\0\0\0\x1f\0\0\0\0\0\0\0\x03\0\0\0\
\x09\0\0\0\x23\0\0\0\0\0\0\0\x03\0\0\0\x05\0\0\0\x08\0\0\0\0\0\0\0\x03\0\0\0\
\x08\0\0\0\x0c\0\0\0\0\0\0\0\x03\0\0\0\x08\0\0\0\x10\0\0\0\0\0\0\0\x03\0\0\0\
\x08\0\0\0\x14\0\0\0\0\0\0\0\x03\0\0\0\x08\0\0\0\x18\0\0\0\0\0\0\0\x03\0\0\0\
\x08\0\0\0\x1c\0\0\0\0\0\0\0\x03\0\0\0\x08\0\0\0\x20\0\0\0\0\0\0\0\x03\0\0\0\
\x08\0\0\0\x24\0\0\0\0\0\0\0\x03\0\0\0\x08\0\0\0\x28\0\0\0\0\0\0\0\x03\0\0\0\
\x08\0\0\0\x2c\0\0\0\0\0\0\0\x03\0\0\0\x08\0\0\0\x30\0\0\0\0\0\0\0\x03\0\0\0\
\x08\0\0\0\x34\0\0\0\0\0\0\0\x03\0\0\0\x08\0\0\0\x38\0\0\0\0\0\0\0\x03\0\0\0\
\x08\0\0\0\x3c\0\0\0\0\0\0\0\x03\0\0\0\x08\0\0\0\x40\0\0\0\0\0\0\0\x03\0\0\0\
\x08\0\0\0\x44\0\0\0\0\0\0\0\x03\0\0\0\x08\0\0\0\x48\0\0\0\0\0\0\0\x03\0\0\0\
\x08\0\0\0\x4c\0\0\0\0\0\0\0\x03\0\0\0\x08\0\0\0\x08\0\0\0\0\0\0\0\x02\0\0\0\
\x0e\0\0\0\x10\0\0\0\0\0\0\0\x02\0\0\0\x04\0\0\0\x18\0\0\0\0\0\0\0\x02\0\0\0\
\x02\0\0\0\xe0\0\0\0\0\0\0\0\x03\0\0\0\x04\0\0\0\xf8\0\0\0\0\0\0\0\x04\0\0\0\
\x0e\0\0\0\x2c\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\x40\0\0\0\0\0\0\0\x04\0\0\0\
\x02\0\0\0\x50\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\x60\0\0\0\0\0\0\0\x04\0\0\0\
\x02\0\0\0\x70\0\0\0\0\0\0\0\x04\0\0\0\x02\0\0\0\x14\0\0\0\0\0\0\0\x03\0\0\0\
\x0a\0\0\0\x18\0\0\0\0\0\0\0\x02\0\0\0\x02\0\0\0\x22\0\0\0\0\0\0\0\x03\0\0\0\
\x0c\0\0\0\x26\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x2a\0\0\0\0\0\0\0\x03\0\0\0\
\x0c\0\0\0\x36\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x4b\0\0\0\0\0\0\0\x03\0\0\0\
\x0c\0\0\0\x60\0\0\0\0\0\0\0\x03\0\0\0\x0c\0\0\0\x7d\0\0\0\0\0\0\0\x02\0\0\0\
\x02\0\0\0\x0d\x0e\x03\0\x2e\x64\x65\x62\x75\x67\x5f\x61\x62\x62\x72\x65\x76\0\
\x2e\x74\x65\x78\x74\0\x2e\x72\x65\x6c\x2e\x42\x54\x46\x2e\x65\x78\x74\0\x68\
\x61\x6e\x64\x6c\x65\x5f\x74\x70\x2e\x5f\x5f\x5f\x5f\x66\x6d\x74\0\x2e\x64\x65\
\x62\x75\x67\x5f\x6c\x6f\x63\x6c\x69\x73\x74\x73\0\x2e\x72\x65\x6c\x2e\x64\x65\
\x62\x75\x67\x5f\x73\x74\x72\x5f\x6f\x66\x66\x73\x65\x74\x73\0\x2e\x64\x65\x62\
\x75\x67\x5f\x73\x74\x72\0\x2e\x64\x65\x62\x75\x67\x5f\x6c\x69\x6e\x65\x5f\x73\
\x74\x72\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x61\x64\x64\x72\0\x68\
\x61\x6e\x64\x6c\x65\x5f\x74\x70\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\
\x69\x6e\x66\x6f\0\x2e\x6c\x6c\x76\x6d\x5f\x61\x64\x64\x72\x73\x69\x67\0\x2e\
\x72\x65\x6c\x74\x72\x61\x63\x65\x70\x6f\x69\x6e\x74\x2f\x73\x79\x73\x63\x61\
\x6c\x6c\x73\x2f\x73\x79\x73\x5f\x65\x6e\x74\x65\x72\x5f\x77\x72\x69\x74\x65\0\
\x6c\x69\x63\x65\x6e\x73\x65\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x6c\
\x69\x6e\x65\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x66\x72\x61\x6d\x65\
\0\x6d\x69\x6e\x69\x6d\x61\x6c\x2e\x62\x70\x66\x2e\x63\0\x2e\x73\x74\x72\x74\
\x61\x62\0\x2e\x73\x79\x6d\x74\x61\x62\0\x2e\x72\x6f\x64\x61\x74\x61\0\x2e\x72\
\x65\x6c\x2e\x42\x54\x46\0\x4c\x49\x43\x45\x4e\x53\x45\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x0d\x01\0\0\x03\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\x3b\x0c\0\0\0\0\0\0\x36\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x0f\0\0\0\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\xb2\0\0\0\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\
\0\0\0\x48\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xae\
\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x88\x09\0\0\0\0\0\0\x10\0\0\
\0\0\0\0\0\x1a\0\0\0\x03\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xd6\0\0\0\
\x01\0\0\0\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x88\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x1d\x01\0\0\x01\0\0\0\x02\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x8c\0\0\0\0\0\0\0\x1c\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x34\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\xa8\0\0\0\0\0\0\0\x16\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xbe\0\
\0\0\0\0\0\0\xee\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\x94\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xac\x01\0\0\0\0\0\0\xe5\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x90\0\0\0\x09\
\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x98\x09\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\
\x1a\0\0\0\x09\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x48\0\0\0\x01\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x91\x02\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x44\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\xe8\x09\0\0\0\0\0\0\x20\x01\0\0\0\0\0\0\x1a\0\0\0\x0b\0\0\0\
\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x5b\0\0\0\x01\0\0\0\x30\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\xe1\x02\0\0\0\0\0\0\xe8\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\
\0\0\0\x01\0\0\0\0\0\0\0\x7a\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\xc9\x03\0\0\0\0\0\0\x20\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\x76\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\x0b\0\0\0\
\0\0\0\x30\0\0\0\0\0\0\0\x1a\0\0\0\x0e\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\
\0\x29\x01\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xec\x03\0\0\0\0\0\0\
\x6d\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x25\x01\
\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x38\x0b\0\0\0\0\0\0\x20\0\0\0\
\0\0\0\0\x1a\0\0\0\x10\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x19\0\0\0\x01\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x5c\x06\0\0\0\0\0\0\x80\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x15\0\0\0\x09\0\0\0\x40\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\x58\x0b\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\x1a\0\0\0\x12\0\
\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xf2\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\xe0\x06\0\0\0\0\0\0\x28\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\xee\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\xa8\x0b\0\0\0\0\0\0\x20\0\0\0\0\0\0\0\x1a\0\0\0\x14\0\0\0\x08\0\0\0\0\0\0\0\
\x10\0\0\0\0\0\0\0\xe2\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\x07\
\0\0\0\0\0\0\x94\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\xde\0\0\0\x09\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xc8\x0b\0\0\0\0\0\0\
\x70\0\0\0\0\0\0\0\x1a\0\0\0\x16\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x66\
\0\0\0\x01\0\0\0\x30\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x9c\x07\0\0\0\0\0\0\x80\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\xa0\0\0\0\x03\
\x4c\xff\x6f\0\0\0\x80\0\0\0\0\0\0\0\0\0\0\0\0\x38\x0c\0\0\0\0\0\0\x03\0\0\0\0\
\0\0\0\x1a\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x15\x01\0\0\x02\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x20\x08\0\0\0\0\0\0\x68\x01\0\0\0\0\0\0\x01\
\0\0\0\x0d\0\0\0\x08\0\0\0\0\0\0\0\x18\0\0\0\0\0\0\0";

	*sz = sizeof(data) - 1;
	return (const void *)data;
}

#ifdef __cplusplus
struct minimal_bpf *minimal_bpf::open(const struct bpf_object_open_opts *opts) { return minimal_bpf__open_opts(opts); }
struct minimal_bpf *minimal_bpf::open_and_load() { return minimal_bpf__open_and_load(); }
int minimal_bpf::load(struct minimal_bpf *skel) { return minimal_bpf__load(skel); }
int minimal_bpf::attach(struct minimal_bpf *skel) { return minimal_bpf__attach(skel); }
void minimal_bpf::detach(struct minimal_bpf *skel) { minimal_bpf__detach(skel); }
void minimal_bpf::destroy(struct minimal_bpf *skel) { minimal_bpf__destroy(skel); }
const void *minimal_bpf::elf_bytes(size_t *sz) { return minimal_bpf__elf_bytes(sz); }
#endif /* __cplusplus */

__attribute__((unused)) static void
minimal_bpf__assert(struct minimal_bpf *s __attribute__((unused)))
{
#ifdef __cplusplus
#define _Static_assert static_assert
#endif
#ifdef __cplusplus
#undef _Static_assert
#endif
}

#endif /* __MINIMAL_BPF_SKEL_H__ */
