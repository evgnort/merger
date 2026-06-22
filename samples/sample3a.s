	movslq	-8304(%rbp), %rcx	# loaded.first,
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vmovdqa	-13200(%rbp), %ymm7	# %sfp, tmp2023
# pipeline_avx2.c:176: /*1*/       __m256i new_indexes1 = _mm256_loadu_si256((__m256i *)&loaded.indexes[loaded.first]); // Load next empty_cnt1 loaded requests indexes
	movq	%rcx, %rax	#,
# pipeline_avx2.c:177: /*1*/       loaded.first += empty_cnt1;
	addl	-12976(%rbp), %eax	# %sfp, _34
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:929:   return *__P;
	vmovdqu	-10352(%rbp,%rcx,4), %ymm4	# MEM[(const __m256i_u * {ref-all})_32], MEM[(const __m256i_u * {ref-all})_32]
# pipeline_avx2.c:177: /*1*/       loaded.first += empty_cnt1;
	movl	%eax, -8304(%rbp)	# _34, loaded.first
# pipeline_avx2.c:179: /*1*/       __m256i new_indexes2 = _mm256_loadu_si256((__m256i *)&loaded.indexes[loaded.first]); // Load next empty_cnt2 loaded requests indexes
	movslq	%eax, %rcx	# _34, _34
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1046:   return (__m256i) __builtin_ia32_permvarsi256 ((__v8si)__X, (__v8si)__Y);
	vpermd	%ymm4, %ymm11, %ymm4	# MEM[(const __m256i_u * {ref-all})_32], unpack_scheme1, tmp1228
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:929:   return *__P;
	vmovdqu	-10352(%rbp,%rcx,4), %ymm3	# MEM[(const __m256i_u * {ref-all})_36], MEM[(const __m256i_u * {ref-all})_36]
# pipeline_avx2.c:180: /*1*/       loaded.first += empty_cnt2;
	movl	-13084(%rbp), %ecx	# %sfp, empty_cnt2
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vpblendvb	%ymm15, %ymm4, %ymm7, %ymm4	# empty_mask1, tmp1228, tmp2023, tmp1230
# pipeline_avx2.c:180: /*1*/       loaded.first += empty_cnt2;
	addl	%ecx, %eax	# empty_cnt2, tmp1226
	movl	%eax, -8304(%rbp)	# tmp1226, loaded.first
# pipeline_avx2.c:182: /*1*/       loaded.count -= empty_cnt1;
	movl	%r11d, %eax	# _42, _42
	subl	-12976(%rbp), %eax	# %sfp, _42
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vmovdqa	-13232(%rbp), %ymm7	# %sfp, tmp2024
# pipeline_avx2.c:183: /*1*/       loaded.count -= empty_cnt2;
	subl	%ecx, %eax	# empty_cnt2, tmp1227
	movl	%eax, -8296(%rbp)	# _42, loaded.count
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1046:   return (__m256i) __builtin_ia32_permvarsi256 ((__v8si)__X, (__v8si)__Y);
	vpermd	%ymm3, %ymm10, %ymm3	# MEM[(const __m256i_u * {ref-all})_36], unpack_scheme2, tmp1229
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vpblendvb	%ymm14, %ymm3, %ymm7, %ymm3	# empty_mask2, tmp1229, tmp2024, tmp1234
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1601:   return (__m256i) __builtin_ia32_gathersiv8si (__src,
	vmovdqa	.LC14(%rip), %ymm7	#, tmp1757
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vmovdqa	%ymm15, -12976(%rbp)	# empty_mask1, %sfp
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1601:   return (__m256i) __builtin_ia32_gathersiv8si (__src,
	vpgatherdd	%ymm7, (%r14,%ymm4,1), %ymm8	# states, tmp1757,, _708
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:935:   *__P = __A;
	vpxor	%xmm7, %xmm7, %xmm7	# tmp2219
	vmovdqu	%ymm7, (%r8)	# tmp2219, MEM[(__m256i_u * {ref-all})_2231]
# pipeline_avx2.c:205:    /*2*/    hashed.first += hashed_valid_cnt;
	addl	%ebx, -64(%rbp)	# _2241, hashed.first
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:181:   return (__m256i) ((__v4du)__A & (__v4du)__B);
	vpand	(%r12), %ymm1, %ymm1	# MEM[(const __m256i_u * {ref-all})_2245], tmp1220, tmp1245
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vmovdqa	-12912(%rbp), %ymm15	# %sfp, _803
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1601:   return (__m256i) __builtin_ia32_gathersiv8si (__src,
	vmovdqa	.LC14(%rip), %ymm9	#, tmp1758
	vmovdqa	.LC14(%rip), %ymm10	#, tmp1759
# pipeline_avx2.c:183: /*1*/       loaded.count -= empty_cnt2;
	movl	%eax, %r11d	# tmp1227, _42
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vmovdqa	%ymm14, %ymm11	# empty_mask2, _704
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:181:   return (__m256i) ((__v4du)__A & (__v4du)__B);
	movq	-12752(%rbp), %rax	# %sfp, _2249
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vpaddd	.LC6(%rip), %ymm4, %ymm14	#, tmp1230, tmp1251
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:684:   return (__m256i)__builtin_ia32_pslldi256 ((__v8si)__A, __B);
	vpslld	$6, %ymm1, %ymm1	#, tmp1245, tmp1243
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vpaddq	%ymm15, %ymm1, %ymm1	# _803, tmp1243, _826
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1601:   return (__m256i) __builtin_ia32_gathersiv8si (__src,
	vpgatherdd	%ymm9, (%r14,%ymm3,1), %ymm7	# states, tmp1758,, _743
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:181:   return (__m256i) ((__v4du)__A & (__v4du)__B);
	vpand	(%rax), %ymm0, %ymm0	# MEM[(const __m256i_u * {ref-all})_2249], tmp1202, tmp1249
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1601:   return (__m256i) __builtin_ia32_gathersiv8si (__src,
	vpgatherdd	%ymm10, (%r14,%ymm14,1), %ymm9	# states, tmp1759,, _831
# pipeline_avx2.c:239:    /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,0); // (2)p0 (MOVQ)
	vmovq	%xmm1, 88(%rdi)	# tmp1256, _2254->next_chain_ref
# pipeline_avx2.c:240:    /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,1); // vpextrq ymm->xmm (p0 + p5) + vpextrq ymm->mem (p237 + p4 + p5)
	vpextrq	$1, %xmm1, 88(%rdx)	# tmp1256, _2257->next_chain_ref
# pipeline_avx2.c:243:    /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,2);
	vextracti128	$0x1, %ymm1, %xmm1	# _826, tmp1260
# pipeline_avx2.c:243:    /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,2);
	vmovq	%xmm1, 88(%rsi)	# tmp1260, _2261->next_chain_ref
# pipeline_avx2.c:244:    /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,3);
	movq	-12784(%rbp), %rax	# %sfp, _2264
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:684:   return (__m256i)__builtin_ia32_pslldi256 ((__v8si)__A, __B);
	vpslld	$6, %ymm0, %ymm0	#, tmp1249, tmp1247
# pipeline_avx2.c:244:    /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,3);
	vpextrq	$1, %xmm1, 88(%rax)	# tmp1260, _2264->next_chain_ref
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vpaddq	%ymm15, %ymm0, %ymm0	# _803, tmp1247, _834
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vpaddd	.LC6(%rip), %ymm3, %ymm14	#, tmp1234, tmp1263
# pipeline_avx2.c:255:    /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,0); 
	movq	-13008(%rbp), %rax	# %sfp, _2268
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1601:   return (__m256i) __builtin_ia32_gathersiv8si (__src,
	vmovdqa	.LC14(%rip), %ymm15	#, tmp1760
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vpaddd	.LC2(%rip), %ymm4, %ymm4	#, tmp1230, _844
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1601:   return (__m256i) __builtin_ia32_gathersiv8si (__src,
	vpgatherdd	%ymm15, (%r14,%ymm14,1), %ymm1	# states, tmp1760,, _856
# pipeline_avx2.c:255:    /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,0); 
	vmovq	%xmm0, 88(%rax)	# tmp1270, _2268->next_chain_ref
# pipeline_avx2.c:256:    /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,1); 
	movq	-13040(%rbp), %rax	# %sfp, _2271
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vpaddd	.LC2(%rip), %ymm3, %ymm3	#, tmp1234, _758
# pipeline_avx2.c:256:    /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,1); 
	vpextrq	$1, %xmm0, 88(%rax)	# tmp1270, _2271->next_chain_ref
# pipeline_avx2.c:262:             if (step2) 
	movl	-12800(%rbp), %r12d	# %sfp,
# pipeline_avx2.c:260:    /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,3); 
	movq	-13072(%rbp), %rax	# %sfp, _2278
# pipeline_avx2.c:259:    /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,2); 
	vextracti128	$0x1, %ymm0, %xmm0	# _834, tmp1274
# pipeline_avx2.c:259:    /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,2); 
	vmovq	%xmm0, 88(%r15)	# tmp1274, _2275->next_chain_ref
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vmovdqa	%ymm4, -13200(%rbp)	# _844, %sfp
	vmovdqa	%ymm3, -13232(%rbp)	# _758, %sfp
# pipeline_avx2.c:260:    /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,3); 
	vpextrq	$1, %xmm0, 88(%rax)	# tmp1274, _2278->next_chain_ref