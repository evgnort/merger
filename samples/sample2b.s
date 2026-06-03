# pipeline_avx2.c:850: /*2*/    uint32_t hashed_valid_cnt = hashed.last - hashed.first;
	movslq	-64(%rbp), %rdx	# hashed.first,
# pipeline_avx2.c:851: /*2*/    hashed_valid_cnt = (hashed_valid_cnt > 8) ? 8 : hashed_valid_cnt;
	movl	$8, %edi	#, tmp1673
# pipeline_avx2.c:850: /*2*/    uint32_t hashed_valid_cnt = hashed.last - hashed.first;
	subl	%edx, %eax	# _68, hashed_valid_cnt
# pipeline_avx2.c:851: /*2*/    hashed_valid_cnt = (hashed_valid_cnt > 8) ? 8 : hashed_valid_cnt;
	cmpl	%edi, %eax	# tmp1673, hashed_valid_cnt
	cmova	%edi, %eax	# hashed_valid_cnt,, tmp1673, hashed_valid_cnt
	salq	$2, %rdx	#, _275
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:519:   return (__m256i) __builtin_ia32_pmovzxdq256 ((__v4si)__X);
	vpmovzxdq	-2112(%rbp,%rdx), %ymm1	# MEM[(const __m128i_u * {ref-all})_73], MEM[(const __m128i_u * {ref-all})_73]
	vpmovzxdq	-2096(%rbp,%rdx), %ymm0	# MEM[(const __m128i_u * {ref-all})_76], MEM[(const __m128i_u * {ref-all})_76]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:569:   return (__m256i)__builtin_ia32_pmuludq256 ((__v8si)__A, (__v8si)__B);
	vpmuludq	%ymm1, %ymm11, %ymm3	# MEM[(const __m128i_u * {ref-all})_73], _1532, tmp1272
	vpmuludq	%ymm1, %ymm12, %ymm1	# MEM[(const __m128i_u * {ref-all})_73], _1531, tmp1275
# pipeline_avx2.c:854: /*2*/    __m256i hashed_indexes = _mm256_loadu_si256((__m256i *)&hashed.indexes[hashed.first]); 
	movq	-12792(%rbp), %rdi	# %sfp, tmp1614
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vmovdqa	-12784(%rbp), %ymm7	# %sfp, _586
# pipeline_avx2.c:854: /*2*/    __m256i hashed_indexes = _mm256_loadu_si256((__m256i *)&hashed.indexes[hashed.first]); 
	addq	%rdx, %rdi	# _275, _71
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:698:   return (__m256i)__builtin_ia32_psllqi256 ((__v4di)__A, __B);
	vpsllq	$32, %ymm3, %ymm3	#, tmp1272, tmp1273
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vpaddq	%ymm3, %ymm1, %ymm1	# tmp1273, tmp1275, _720
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:569:   return (__m256i)__builtin_ia32_pmuludq256 ((__v8si)__A, (__v8si)__B);
	vpmuludq	%ymm0, %ymm11, %ymm3	# MEM[(const __m128i_u * {ref-all})_76], _1532, tmp1276
	vpmuludq	%ymm0, %ymm12, %ymm0	# MEM[(const __m128i_u * {ref-all})_76], _1531, tmp1279
	vpmuludq	%ymm6, %ymm1, %ymm5	# _1530, _720, tmp1280
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:789:   return (__m256i)__builtin_ia32_psrlqi256 ((__v4di)__A, __B);
	vpsrlq	$32, %ymm1, %ymm1	#, _720, tmp1283
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:569:   return (__m256i)__builtin_ia32_pmuludq256 ((__v8si)__A, (__v8si)__B);
	vpmuludq	%ymm6, %ymm1, %ymm1	# _1530, tmp1283, tmp1285
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:698:   return (__m256i)__builtin_ia32_psllqi256 ((__v4di)__A, __B);
	vpsllq	$32, %ymm3, %ymm3	#, tmp1276, tmp1277
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vpaddq	%ymm3, %ymm0, %ymm0	# tmp1277, tmp1279, _709
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:569:   return (__m256i)__builtin_ia32_pmuludq256 ((__v8si)__A, (__v8si)__B);
	vpmuludq	%ymm6, %ymm0, %ymm3	# _1530, _709, tmp1286
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:789:   return (__m256i)__builtin_ia32_psrlqi256 ((__v4di)__A, __B);
	vpsrlq	$32, %ymm0, %ymm0	#, _709, tmp1289
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:569:   return (__m256i)__builtin_ia32_pmuludq256 ((__v8si)__A, (__v8si)__B);
	vpmuludq	%ymm6, %ymm0, %ymm0	# _1530, tmp1289, tmp1291
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:789:   return (__m256i)__builtin_ia32_psrlqi256 ((__v4di)__A, __B);
	vpsrlq	$32, %ymm5, %ymm5	#, tmp1280, tmp1281
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vpaddq	%ymm5, %ymm1, %ymm1	# tmp1281, tmp1285, tmp1293
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:789:   return (__m256i)__builtin_ia32_psrlqi256 ((__v4di)__A, __B);
	vpsrlq	$32, %ymm3, %ymm3	#, tmp1286, tmp1287
	vpsrlq	$32, %ymm1, %ymm1	#, tmp1293, tmp1292
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vpaddd	.LC9(%rip), %ymm1, %ymm1	#, tmp1292, tmp1300
# pipeline_avx2.c:863: /*2*/    __m256i m1 = _mm256_loadu_si256((__m256i*)&cnt2mask[8-hashed_valid_cnt]);
	movl	$8, %edx	#, tmp1297
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vpaddq	%ymm3, %ymm0, %ymm0	# tmp1287, tmp1291, tmp1305
# pipeline_avx2.c:863: /*2*/    __m256i m1 = _mm256_loadu_si256((__m256i*)&cnt2mask[8-hashed_valid_cnt]);
	subl	%eax, %edx	# hashed_valid_cnt, tmp1298
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:789:   return (__m256i)__builtin_ia32_psrlqi256 ((__v4di)__A, __B);
	vpsrlq	$32, %ymm0, %ymm0	#, tmp1305, tmp1304
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:929:   return *__P;
	vmovdqu	(%rdi), %ymm2	# MEM[(const __m256i_u * {ref-all})_71], MEM[(const __m256i_u * {ref-all})_71]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:181:   return (__m256i) ((__v4du)__A & (__v4du)__B);
	vpand	-12560(%rbp,%rdx,8), %ymm1, %ymm1	# MEM[(const __m256i_u * {ref-all})_84], tmp1300, tmp1302
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vpaddd	.LC9(%rip), %ymm0, %ymm0	#, tmp1304, tmp1312
# pipeline_avx2.c:864: /*2*/    __m256i m2 = _mm256_loadu_si256((__m256i*)&cnt2mask[12-hashed_valid_cnt]);
	movl	$12, %edx	#, tmp1309
	subl	%eax, %edx	# hashed_valid_cnt, tmp1310
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:181:   return (__m256i) ((__v4du)__A & (__v4du)__B);
	vpand	-12560(%rbp,%rdx,8), %ymm0, %ymm0	# MEM[(const __m256i_u * {ref-all})_86], tmp1312, tmp1314
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:684:   return (__m256i)__builtin_ia32_pslldi256 ((__v8si)__A, __B);
	vpslld	$6, %ymm1, %ymm1	#, tmp1302, tmp1295
# pipeline_avx2.c:887: /*2*/    uint64_t idx2 = PART_64_256(hashed_indexes,0); // (2)p0 (MOVD), (2)p0 (MOVQ)
	vmovq	%xmm2, %rdx	# tmp1316, _87
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vpaddq	%ymm7, %ymm1, %ymm1	# _586, tmp1295, _666
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:935:   *__P = __A;
	vmovdqu	%ymm9, (%rdi)	# tmp1636, MEM[(__m256i_u * {ref-all})_71]
# pipeline_avx2.c:888: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,0); // (2)p0 (MOVQ)
	movl	%edx, %edi	# _87, _87
# pipeline_avx2.c:889: /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,1); // vpextrq ymm->xmm (p0 + p5) + vpextrq ymm->mem (p237 + p4 + p5)
	shrq	$32, %rdx	#, tmp1320
# pipeline_avx2.c:888: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,0); // (2)p0 (MOVQ)
	vmovq	%xmm1, 88(%r15,%rdi)	# tmp1319, _90->next_chain_ref
# pipeline_avx2.c:889: /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,1); // vpextrq ymm->xmm (p0 + p5) + vpextrq ymm->mem (p237 + p4 + p5)
	vpextrq	$1, %xmm1, 88(%r15,%rdx)	# tmp1319, _94->next_chain_ref
# pipeline_avx2.c:891: /*2*/    idx2 = PART_64_256(hashed_indexes,1); // (2)p0 (MOVD), (2)p0 (MOVQ)
	vpextrq	$1, %xmm2, %rdx	# tmp1316, _96
# pipeline_avx2.c:892: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,2);
	movl	%edx, %edi	# _96, _96
# pipeline_avx2.c:892: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,2);
	vextracti128	$0x1, %ymm1, %xmm1	# _666, tmp1326
# pipeline_avx2.c:893: /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,3);
	shrq	$32, %rdx	#, tmp1327
# pipeline_avx2.c:892: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,2);
	vmovq	%xmm1, 88(%r15,%rdi)	# tmp1326, _99->next_chain_ref
# pipeline_avx2.c:893: /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs1,3);
	vpextrq	$1, %xmm1, 88(%r15,%rdx)	# tmp1326, _103->next_chain_ref
# pipeline_avx2.c:897: /*2*/    idx2 = PART_64_256(hashed_indexes,2); // (2)p0 (MOVD), (2)p0 (MOVQ)
	vextracti128	$0x1, %ymm2, %xmm1	# MEM[(const __m256i_u * {ref-all})_71], tmp1330
	vmovq	%xmm1, %rdx	# tmp1330, _105
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:684:   return (__m256i)__builtin_ia32_pslldi256 ((__v8si)__A, __B);
	vpslld	$6, %ymm0, %ymm0	#, tmp1314, tmp1307
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:128:   return (__m256i) ((__v4du)__A + (__v4du)__B);
	vpaddq	%ymm7, %ymm0, %ymm0	# _586, tmp1307, _663
# pipeline_avx2.c:898: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,0); 
	movl	%edx, %edi	# _105, _105
# pipeline_avx2.c:899: /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,1);
	shrq	$32, %rdx	#, tmp1334
# pipeline_avx2.c:898: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,0); 
	vmovq	%xmm0, 88(%r15,%rdi)	# tmp1333, _108->next_chain_ref
# pipeline_avx2.c:899: /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,1);
	vpextrq	$1, %xmm0, 88(%r15,%rdx)	# tmp1333, _112->next_chain_ref
# pipeline_avx2.c:901: /*2*/    idx2 = PART_64_256(hashed_indexes,3); // (2)p0 (MOVQ), (2)p0 (MOVD)
	vpextrq	$1, %xmm1, %rdx	# tmp1330, _114
# pipeline_avx2.c:902: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,2);
	movl	%edx, %edi	# _114, _114
# pipeline_avx2.c:902: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,2);
	vextracti128	$0x1, %ymm0, %xmm0	# _663, tmp1340
# pipeline_avx2.c:902: /*2*/    ((FProcessState *)((char *)states + (uint32_t)idx2))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,2);
	vmovq	%xmm0, 88(%r15,%rdi)	# tmp1340, _117->next_chain_ref
# pipeline_avx2.c:923: /*2*/    hcnt += hashed_valid_cnt;
	movl	-12796(%rbp), %edi	# %sfp, hcnt
# pipeline_avx2.c:903: /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,3);
	shrq	$32, %rdx	#, tmp1341
# pipeline_avx2.c:861: /*2*/    hashed.first += hashed_valid_cnt;
	addl	%eax, -64(%rbp)	# hashed_valid_cnt, hashed.first
# pipeline_avx2.c:923: /*2*/    hcnt += hashed_valid_cnt;
	addl	%eax, %edi	# hashed_valid_cnt, hcnt
# pipeline_avx2.c:903: /*2*/    ((FProcessState *)((char *)states + (idx2 >> 32LL)))->next_chain_ref = (uint32_t *)PART_64_256(hashed_refs2,3);
	vpextrq	$1, %xmm0, 88(%r15,%rdx)	# tmp1340, _121->next_chain_ref