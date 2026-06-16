# pipeline_avx2.c:1009:    /*2*/    FProcessState * restrict dstate_w = dstates_w[i]; // (4)p23 (MOV)
	movq	(%rdi), %rdx	# MEM[(struct FProcessState * *)_1464], dstate_w
# pipeline_avx2.c:1010:    /*2*/    __m256i *kb = (__m256i *)dstate_w->key_buf,*dr = (__m256i *)dstate_w->cur_data_ref,*ot = (__m256i *)output; // No op
	movq	72(%rdx), %rsi	# dstate_w_558->cur_data_ref, dr
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:929:   return *__P;
	vmovdqu	(%rdx), %ymm0	# MEM[(const __m256i_u * {ref-all})dstate_w_558], MEM[(const __m256i_u * {ref-all})dstate_w_558]
# pipeline_avx2.c:1013:    /*2*/    int ks = dstate_w->key_size;
	movl	120(%rdx), %r9d	# dstate_w_558->key_size, ks
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:929:   return *__P;
	vmovdqu	(%rsi), %ymm1	# MEM[(const __m256i_u * {ref-all})dr_560], MEM[(const __m256i_u * {ref-all})dr_560]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:935:   *__P = __A;
	vmovdqu	%ymm0, (%rbx)	# MEM[(const __m256i_u * {ref-all})dstate_w_558], MEM[(__m256i_u * {ref-all})output_233]
	
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:233:   return (__m256i) ((__v32qi)__A == (__v32qi)__B);
	vpcmpeqb	%ymm1, %ymm0, %ymm0	# MEM[(const __m256i_u * {ref-all})dr_560], MEM[(const __m256i_u * {ref-all})dstate_w_558], tmp1564
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:435:   return __builtin_ia32_pmovmskb256 ((__v32qi)__A);
	vpmovmskb	%ymm0, %eax	# tmp1564, tmp1561
# pipeline_avx2.c:1017:    /*2*/    int bnum = _tzcnt_u32(~cmpmask); // (1)p0156 -> (3)p1 (TZCNT)
	notl	%eax	# tmp1567
# pipeline_avx2.c:1017:    /*2*/    int bnum = _tzcnt_u32(~cmpmask); // (1)p0156 -> (3)p1 (TZCNT)
	tzcntl	%eax, %eax	# tmp1567, bnum
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmiintrin.h:88:   return __X & (__X - 1);
	blsr	68(%rdx), %ecx	# dstate_w_558->items_mask, tmp1570
	movl	%ecx, 68(%rdx)	# tmp1570, dstate_w_558->items_mask
# pipeline_avx2.c:1029:    /*2*/    int found = (bnum >= ks);
	xorl	%ecx, %ecx	# tmp1571
	cmpl	%eax, %r9d	# bnum, ks
# pipeline_avx2.c:1031:    /*2*/    output[dstate_w->key_size] = '\n';
	movslq	120(%rdx), %rax	# dstate_w_558->key_size, dstate_w_558->key_size
# pipeline_avx2.c:1029:    /*2*/    int found = (bnum >= ks);
	setle	%cl	#, tmp1571
# pipeline_avx2.c:1031:    /*2*/    output[dstate_w->key_size] = '\n';
	movb	$10, (%rbx,%rax)	#, *_216
# pipeline_avx2.c:1034:    /*2*/    int wsnumd = (1 - found) * ((dstate_w->items_mask ? 2:0) + dstate_w->chain_cont);
	xorl	%r8d, %r8d	# tmp1579
# pipeline_avx2.c:1032:    /*2*/    output += found * (dstate_w->key_size + 1);
	movl	120(%rdx), %eax	# dstate_w_558->key_size, tmp1957
# pipeline_avx2.c:1034:    /*2*/    int wsnumd = (1 - found) * ((dstate_w->items_mask ? 2:0) + dstate_w->chain_cont);
	movl	68(%rdx), %r9d	# dstate_w_558->items_mask,
# pipeline_avx2.c:1032:    /*2*/    output += found * (dstate_w->key_size + 1);
	incl	%eax	# tmp1575
# pipeline_avx2.c:1032:    /*2*/    output += found * (dstate_w->key_size + 1);
	imull	%ecx, %eax	# tmp1571, tmp1577
# pipeline_avx2.c:1035:             FPStateParams dps = dstate_w->sp;
	movl	108(%rdx), %esi	# dstate_w_558->sp.inc, dps$inc
# pipeline_avx2.c:1032:    /*2*/    output += found * (dstate_w->key_size + 1);
	cltq
# pipeline_avx2.c:1032:    /*2*/    output += found * (dstate_w->key_size + 1);
	addq	%rax, %rbx	# tmp1578, output
# pipeline_avx2.c:1034:    /*2*/    int wsnumd = (1 - found) * ((dstate_w->items_mask ? 2:0) + dstate_w->chain_cont);
	testl	%r9d, %r9d	#
# pipeline_avx2.c:1034:    /*2*/    int wsnumd = (1 - found) * ((dstate_w->items_mask ? 2:0) + dstate_w->chain_cont);
	movl	64(%rdx), %eax	# dstate_w_558->chain_cont, dstate_w_558->chain_cont
# pipeline_avx2.c:1034:    /*2*/    int wsnumd = (1 - found) * ((dstate_w->items_mask ? 2:0) + dstate_w->chain_cont);
	setne	%r8b	#, tmp1579
# pipeline_avx2.c:1034:    /*2*/    int wsnumd = (1 - found) * ((dstate_w->items_mask ? 2:0) + dstate_w->chain_cont);
	leal	(%rax,%r8,2), %eax	#, tmp1582
# pipeline_avx2.c:1034:    /*2*/    int wsnumd = (1 - found) * ((dstate_w->items_mask ? 2:0) + dstate_w->chain_cont);
	movl	%r10d, %r8d	# tmp1585, tmp1584
	subl	%ecx, %r8d	# tmp1571, tmp1584
# pipeline_avx2.c:1034:    /*2*/    int wsnumd = (1 - found) * ((dstate_w->items_mask ? 2:0) + dstate_w->chain_cont);
	imull	%r8d, %eax	# tmp1584, wsnumd
# pipeline_avx2.c:1036:    /*2*/    worksets[wsnumd]->indexes[worksets[wsnumd]->last] = dps.offset;
	movl	104(%rdx), %edx	# dstate_w_558->sp.offset, dstate_w_558->sp.offset
# pipeline_avx2.c:1007:          for(i = 0; i < 8; i++)
	addq	$8, %rdi	#, ivtmp.131
# pipeline_avx2.c:1036:    /*2*/    worksets[wsnumd]->indexes[worksets[wsnumd]->last] = dps.offset;
	cltq
	movq	-12720(%rbp,%rax,8), %rcx	# worksets[wsnumd_572], _228
# pipeline_avx2.c:1036:    /*2*/    worksets[wsnumd]->indexes[worksets[wsnumd]->last] = dps.offset;
	movslq	2052(%rcx), %r8	# _228->last,
	movq	%r8, %rax	#,
# pipeline_avx2.c:1037:    /*2*/    worksets[wsnumd]->last += dps.inc;
	addl	%esi, %eax	# dps$inc, tmp1590
# pipeline_avx2.c:1036:    /*2*/    worksets[wsnumd]->indexes[worksets[wsnumd]->last] = dps.offset;
	movl	%edx, (%rcx,%r8,4)	# dstate_w_558->sp.offset, _228->indexes[_230]
# pipeline_avx2.c:1037:    /*2*/    worksets[wsnumd]->last += dps.inc;
	movl	%eax, 2052(%rcx)	# tmp1590, _228->last
# pipeline_avx2.c:1007:          for(i = 0; i < 8; i++)

