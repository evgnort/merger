# pipeline_avx2.c:979: /*1*/       FProcessState * restrict hstate_w = hstates_w[i]; // (4)p23 (MOV)
	movq	(%rdi), %rcx	# MEM[(struct FProcessState * *)_1470], hstate_w
# pipeline_avx2.c:981: /*1*/       uint32_t tmp = *((uint32_t *)hstate_w->key_buf); // (4)p23 (MOV)  Trick to force compiler to one data load 
	vmovd	(%rcx), %xmm0	# MEM[(uint32_t *)hstate_w_583],
# pipeline_avx2.c:982: /*1*/       uint32_t * restrict chain_ref = hstate_w->cur_chain_ref = hstate_w->next_chain_ref; // (4)p23 (MOV) -> (2)p237->(1)p4
	movq	88(%rcx), %rsi	# hstate_w_583->next_chain_ref, _180
# pipeline_avx2.c:981: /*1*/       uint32_t tmp = *((uint32_t *)hstate_w->key_buf); // (4)p23 (MOV)  Trick to force compiler to one data load 
	vmovq	%xmm0, %rax	#,
# pipeline_avx2.c:984: /*1*/       uint32_t src_bits = 0x7FF * (((tmp >> 8) & 0x1) + ((tmp & 0x200) << 7)); // (1)p06 (SHR) -> (1)p0156 (AND) + (1)p0156 (AND) -> (1)p06 (SHL)
	movl	%eax, %edx	# tmp, tmp1510
	shrl	$8, %edx	#, tmp1510
# pipeline_avx2.c:984: /*1*/       uint32_t src_bits = 0x7FF * (((tmp >> 8) & 0x1) + ((tmp & 0x200) << 7)); // (1)p06 (SHR) -> (1)p0156 (AND) + (1)p0156 (AND) -> (1)p06 (SHL)
	sall	$7, %eax	#, tmp1512
# pipeline_avx2.c:984: /*1*/       uint32_t src_bits = 0x7FF * (((tmp >> 8) & 0x1) + ((tmp & 0x200) << 7)); // (1)p06 (SHR) -> (1)p0156 (AND) + (1)p0156 (AND) -> (1)p06 (SHL)
	andl	$1, %edx	#, tmp1511
# pipeline_avx2.c:984: /*1*/       uint32_t src_bits = 0x7FF * (((tmp >> 8) & 0x1) + ((tmp & 0x200) << 7)); // (1)p06 (SHR) -> (1)p0156 (AND) + (1)p0156 (AND) -> (1)p06 (SHL)
	andl	$65536, %eax	#, tmp1513
# pipeline_avx2.c:984: /*1*/       uint32_t src_bits = 0x7FF * (((tmp >> 8) & 0x1) + ((tmp & 0x200) << 7)); // (1)p06 (SHR) -> (1)p0156 (AND) + (1)p0156 (AND) -> (1)p06 (SHL)
	orl	%edx, %eax	# tmp1511, tmp1514
# pipeline_avx2.c:982: /*1*/       uint32_t * restrict chain_ref = hstate_w->cur_chain_ref = hstate_w->next_chain_ref; // (4)p23 (MOV) -> (2)p237->(1)p4
	movq	%rsi, 80(%rcx)	# _180, hstate_w_583->cur_chain_ref
# pipeline_avx2.c:984: /*1*/       uint32_t src_bits = 0x7FF * (((tmp >> 8) & 0x1) + ((tmp & 0x200) << 7)); // (1)p06 (SHR) -> (1)p0156 (AND) + (1)p0156 (AND) -> (1)p06 (SHL)
	movl	%eax, %edx	# tmp1514, tmp1516
	sall	$11, %edx	#, tmp1516
# /usr/lib/gcc/x86_64-linux-gnu/11/include/emmintrin.h:592:   return __extension__ (__m128i)(__v2di){ __q0, __q1 };
	vmovq	%xmm0, %xmm0	# tmp, tmp1506
# pipeline_avx2.c:984: /*1*/       uint32_t src_bits = 0x7FF * (((tmp >> 8) & 0x1) + ((tmp & 0x200) << 7)); // (1)p06 (SHR) -> (1)p0156 (AND) + (1)p0156 (AND) -> (1)p06 (SHL)
	subl	%eax, %edx	# tmp1514, src_bits
# /usr/lib/gcc/x86_64-linux-gnu/11/include/tmmintrin.h:138:   return (__m128i) __builtin_ia32_pshufb128 ((__v16qi)__X, (__v16qi)__Y);
	vpshufb	%xmm1, %xmm0, %xmm0	# tmp1509, tmp1506, tmp1508
# /usr/lib/gcc/x86_64-linux-gnu/11/include/emmintrin.h:1335:   return (__m128i) ((__v16qi)__A == (__v16qi)__B);
	vpcmpeqb	(%rsi), %xmm0, %xmm0	# MEM[(const __m128i_u * {ref-all})_180], tmp1508, tmp1523
# pipeline_avx2.c:992: /*1*/       uint32_t bit_res = ~(chain_ref[3] ^ src_bits); 
	xorl	12(%rsi), %edx	# MEM[(uint32_t *)_180 + 12B], tmp1518
# pipeline_avx2.c:992: /*1*/       uint32_t bit_res = ~(chain_ref[3] ^ src_bits); 
	notl	%edx	# bit_res
# pipeline_avx2.c:995: /*1*/       uint32_t items_mask = _mm_movemask_epi8(cmpres) & bit_res & (bit_res >> 16) & 0x7FF;
	movl	%edx, %eax	# bit_res, tmp1525
# /usr/lib/gcc/x86_64-linux-gnu/11/include/emmintrin.h:1433:   return __builtin_ia32_pmovmskb128 ((__v16qi)__A);
	vpmovmskb	%xmm0, %r10d	# tmp1523, tmp1519
# pipeline_avx2.c:995: /*1*/       uint32_t items_mask = _mm_movemask_epi8(cmpres) & bit_res & (bit_res >> 16) & 0x7FF;
	shrl	$16, %eax	#, tmp1525
# pipeline_avx2.c:995: /*1*/       uint32_t items_mask = _mm_movemask_epi8(cmpres) & bit_res & (bit_res >> 16) & 0x7FF;
	andl	%r10d, %eax	# tmp1519, tmp1526
	andl	%edx, %eax	# bit_res, tmp1527
# pipeline_avx2.c:997: /*1*/       hstate_w->next_chain_ref = (uint32_t *)&ht->table[(int64_t)chain_ref[15] * CACHE_LINE_SIZE];
	movl	60(%rsi), %edx	# MEM[(uint32_t *)_180 + 60B],
# pipeline_avx2.c:995: /*1*/       uint32_t items_mask = _mm_movemask_epi8(cmpres) & bit_res & (bit_res >> 16) & 0x7FF;
	andl	$2047, %eax	#, items_mask
# pipeline_avx2.c:997: /*1*/       hstate_w->next_chain_ref = (uint32_t *)&ht->table[(int64_t)chain_ref[15] * CACHE_LINE_SIZE];
	movq	%rdx, %rsi	#,
# pipeline_avx2.c:997: /*1*/       hstate_w->next_chain_ref = (uint32_t *)&ht->table[(int64_t)chain_ref[15] * CACHE_LINE_SIZE];
	salq	$6, %rdx	#, tmp1529
# pipeline_avx2.c:997: /*1*/       hstate_w->next_chain_ref = (uint32_t *)&ht->table[(int64_t)chain_ref[15] * CACHE_LINE_SIZE];
	addq	%r9, %rdx	# _193, tmp1530
	movq	%rdx, 88(%rcx)	# tmp1530, hstate_w_583->next_chain_ref
# pipeline_avx2.c:998:             hstate_w->chain_cont = chain_ref[15] ? 1 : 0;
	xorl	%r10d, %r10d	# tmp1531
# pipeline_avx2.c:999: /*1*/       hstate_w->items_mask = items_mask << 4; // Shifting by 4 to start of refs in table cacheline to remove 3 component addressing
	movl	%eax, %edx	# items_mask, tmp1534
# pipeline_avx2.c:998:             hstate_w->chain_cont = chain_ref[15] ? 1 : 0;
	testl	%esi, %esi	# _194
	setne	%r10b	#, tmp1531
# pipeline_avx2.c:999: /*1*/       hstate_w->items_mask = items_mask << 4; // Shifting by 4 to start of refs in table cacheline to remove 3 component addressing
	sall	$4, %edx	#, tmp1534
# pipeline_avx2.c:1001: /*1*/       int wsnum = (items_mask ? 2:0) + hstate_w->chain_cont;
	testl	%eax, %eax	# items_mask
	setne	%al	#, tmp1535
	movzbl	%al, %eax	# tmp1535, tmp1535
# pipeline_avx2.c:1001: /*1*/       int wsnum = (items_mask ? 2:0) + hstate_w->chain_cont;
	leal	(%r10,%rax,2), %eax	#, wsnum
# pipeline_avx2.c:998:             hstate_w->chain_cont = chain_ref[15] ? 1 : 0;
	vmovd	%r10d, %xmm0	# tmp1531, tmp1531
# pipeline_avx2.c:1003: /*1*/       worksets[wsnum]->indexes[worksets[wsnum]->last] = hps.offset;
	cltq
# pipeline_avx2.c:998:             hstate_w->chain_cont = chain_ref[15] ? 1 : 0;
	vpinsrd	$1, %edx, %xmm0, %xmm0	# tmp1534, tmp1531, tmp1533
# pipeline_avx2.c:1003: /*1*/       worksets[wsnum]->indexes[worksets[wsnum]->last] = hps.offset;
	movq	-12720(%rbp,%rax,8), %rdx	# worksets[wsnum_592], _203
# pipeline_avx2.c:998:             hstate_w->chain_cont = chain_ref[15] ? 1 : 0;
	vmovq	%xmm0, 64(%rcx)	# tmp1533, MEM <vector(2) unsigned int> [(unsigned int *)hstate_w_583 + 64B]
# pipeline_avx2.c:1003: /*1*/       worksets[wsnum]->indexes[worksets[wsnum]->last] = hps.offset;
	movslq	2052(%rdx), %r10	# _203->last,
# pipeline_avx2.c:1002:             FPStateParams hps = hstate_w->sp;
	movl	108(%rcx), %esi	# hstate_w_583->sp.inc, hps$inc
# pipeline_avx2.c:1003: /*1*/       worksets[wsnum]->indexes[worksets[wsnum]->last] = hps.offset;
	movq	%r10, %rax	#,
# pipeline_avx2.c:1003: /*1*/       worksets[wsnum]->indexes[worksets[wsnum]->last] = hps.offset;
	movl	104(%rcx), %ecx	# hstate_w_583->sp.offset, hstate_w_583->sp.offset
# pipeline_avx2.c:1004: /*1*/       worksets[wsnum]->last += hps.inc;
	addl	%esi, %eax	# hps$inc, tmp1542
# pipeline_avx2.c:977:          for(i = 0; i < 8; i++)
	addq	$8, %rdi	#, ivtmp.138
# pipeline_avx2.c:1003: /*1*/       worksets[wsnum]->indexes[worksets[wsnum]->last] = hps.offset;
	movl	%ecx, (%rdx,%r10,4)	# hstate_w_583->sp.offset, _203->indexes[_204]
# pipeline_avx2.c:1004: /*1*/       worksets[wsnum]->last += hps.inc;
	movl	%eax, 2052(%rdx)	# tmp1542, _203->last