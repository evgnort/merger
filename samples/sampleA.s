# pipeline_avx2.c:740: /*1*/       __m256i new_indexes1 = _mm256_loadu_si256((__m256i *)&loaded.indexes[loaded.first]); // Load next empty_cnt1 loaded requests indexes
	movslq	-8304(%rbp), %r8	# loaded.first,
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vmovdqa	-13072(%rbp), %ymm5	# %sfp, tmp1913
# pipeline_avx2.c:740: /*1*/       __m256i new_indexes1 = _mm256_loadu_si256((__m256i *)&loaded.indexes[loaded.first]); // Load next empty_cnt1 loaded requests indexes
	movq	%r8, %rdx	#,
# pipeline_avx2.c:741: /*1*/       loaded.first += empty_cnt1;
	addl	%r14d, %edx	# empty_cnt1, _34
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:929:   return *__P;
	vmovdqu	-10352(%rbp,%r8,4), %ymm3	# MEM[(const __m256i_u * {ref-all})_32], MEM[(const __m256i_u * {ref-all})_32]
# pipeline_avx2.c:741: /*1*/       loaded.first += empty_cnt1;
	movl	%edx, -8304(%rbp)	# _34, loaded.first
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vmovdqa	-12976(%rbp), %ymm7	# %sfp, tmp1914
# pipeline_avx2.c:743: /*1*/       __m256i new_indexes2 = _mm256_loadu_si256((__m256i *)&loaded.indexes[loaded.first]); // Load next empty_cnt2 loaded requests indexes
	movslq	%edx, %r8	# _34, _34
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:929:   return *__P;
	vmovdqu	-10352(%rbp,%r8,4), %ymm2	# MEM[(const __m256i_u * {ref-all})_36], MEM[(const __m256i_u * {ref-all})_36]
# pipeline_avx2.c:746: /*1*/       loaded.count -= empty_cnt1;
	subl	%r14d, %edi	# empty_cnt1, tmp1119
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1046:   return (__m256i) __builtin_ia32_permvarsi256 ((__v8si)__X, (__v8si)__Y);
	vpermd	%ymm3, %ymm13, %ymm3	# MEM[(const __m256i_u * {ref-all})_32], unpack_scheme1, tmp1121
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vpblendvb	%ymm7, %ymm3, %ymm5, %ymm3	# tmp1914, tmp1121, tmp1913, tmp1123
# pipeline_avx2.c:744: /*1*/       loaded.first += empty_cnt2;
	addl	%r15d, %edx	# empty_cnt2, tmp1118
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vmovdqa	-13104(%rbp), %ymm5	# %sfp, tmp1915
	vmovdqa	-13008(%rbp), %ymm7	# %sfp, tmp1916
# pipeline_avx2.c:747: /*1*/       loaded.count -= empty_cnt2;
	subl	%r15d, %edi	# empty_cnt2, tmp1120
# pipeline_avx2.c:744: /*1*/       loaded.first += empty_cnt2;
	movl	%edx, -8304(%rbp)	# tmp1118, loaded.first
# pipeline_avx2.c:747: /*1*/       loaded.count -= empty_cnt2;
	movl	%edi, -8296(%rbp)	# tmp1120, loaded.count
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1046:   return (__m256i) __builtin_ia32_permvarsi256 ((__v8si)__X, (__v8si)__Y);
	vpermd	%ymm2, %ymm8, %ymm2	# MEM[(const __m256i_u * {ref-all})_36], unpack_scheme2, tmp1122
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vpblendvb	%ymm7, %ymm2, %ymm5, %ymm2	# tmp1916, tmp1122, tmp1915, tmp1127
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vpaddd	.LC5(%rip), %ymm3, %ymm0	#, tmp1123, tmp1135
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1601:   return (__m256i) __builtin_ia32_gathersiv8si (__src,
	vmovdqa	.LC14(%rip), %ymm5	#, tmp1674
	vmovdqa	.LC14(%rip), %ymm1	#, tmp1675
	vmovdqa	.LC14(%rip), %ymm8	#, tmp1676
	vpgatherdd	%ymm5, 0(%r13,%ymm3,1), %ymm7	# states, tmp1674,, _650
	vpgatherdd	%ymm1, 0(%r13,%ymm2,1), %ymm5	# states, tmp1675,, _648
	vpgatherdd	%ymm8, 0(%r13,%ymm0,1), %ymm1	# states, tmp1676,, _642
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vpaddd	.LC5(%rip), %ymm2, %ymm0	#, tmp1127, tmp1139
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1601:   return (__m256i) __builtin_ia32_gathersiv8si (__src,
	vmovdqa	.LC14(%rip), %ymm8	#, tmp1677
	vmovdqa	%ymm1, -13040(%rbp)	# _642, %sfp
	vpgatherdd	%ymm8, 0(%r13,%ymm0,1), %ymm13	# states, tmp1677,, _640
	vmovdqa	%ymm13, -12816(%rbp)	# _640, %sfp
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:684:   return (__m256i)__builtin_ia32_pslldi256 ((__v8si)__A, __B);
	vpslld	$5, %ymm15, %ymm1	#, hashes1, tmp1147
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:775:   return (__m256i)__builtin_ia32_psrldi256 ((__v8si)__A, __B);
	vpsrld	$27, %ymm15, %ymm13	#, hashes1, tmp1145
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vpaddd	.LC2(%rip), %ymm3, %ymm3	#, tmp1123, _637
	vpaddd	.LC2(%rip), %ymm2, %ymm2	#, tmp1127, _635
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:576:   return (__m256i) ((__v4du)__A | (__v4du)__B);
	vpor	%ymm13, %ymm1, %ymm1	# tmp1145, tmp1147, tmp1154
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vmovdqa	-12976(%rbp), %ymm13	# %sfp, tmp1923
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:775:   return (__m256i)__builtin_ia32_psrldi256 ((__v8si)__A, __B);
	vpsrld	$27, %ymm4, %ymm8	#, hashes2, tmp1149
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:684:   return (__m256i)__builtin_ia32_pslldi256 ((__v8si)__A, __B);
	vpslld	$5, %ymm4, %ymm0	#, hashes2, tmp1151
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vpblendvb	%ymm13, .LC6(%rip), %ymm1, %ymm1	# tmp1923,, tmp1154, tmp1153
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:121:   return (__m256i) ((__v8su)__A + (__v8su)__B);
	vmovdqa	%ymm3, -13072(%rbp)	# _637, %sfp
	vmovdqa	%ymm2, -13104(%rbp)	# _635, %sfp
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:576:   return (__m256i) ((__v4du)__A | (__v4du)__B);
	vpor	%ymm8, %ymm0, %ymm0	# tmp1149, tmp1151, tmp1159
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vmovdqa	-13008(%rbp), %ymm8	# %sfp, tmp1924
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmi2intrin.h:71:   return __builtin_ia32_pdep_di (__X, __Y);
	movabsq	$72340172838076673, %r11	#, tmp1927
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vpblendvb	%ymm8, .LC6(%rip), %ymm0, %ymm0	# tmp1924,, tmp1159, tmp1158
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:915:   return (__m256i) ((__v4du)__A ^ (__v4du)__B);
	vpxor	%ymm0, %ymm5, %ymm0	# tmp1158, _648, tmp1174
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:247:   return (__m256i) ((__v8si)__A == (__v8si)__B);
	vpcmpeqd	%ymm10, %ymm5, %ymm5	# tmp1631, _648, tmp1181
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:562:   return (__m256i) ((__v8su)__A * (__v8su)__B);
	vpmulld	.LC7(%rip), %ymm0, %ymm0	#, tmp1174, tmp1175
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:915:   return (__m256i) ((__v4du)__A ^ (__v4du)__B);
	vpxor	%ymm1, %ymm7, %ymm1	# tmp1153, _650, tmp1164
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vpblendvb	%ymm5, %ymm4, %ymm0, %ymm0	# tmp1181, hashes2, tmp1175, tmp1173
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:247:   return (__m256i) ((__v8si)__A == (__v8si)__B);
	vpcmpeqd	-13040(%rbp), %ymm10, %ymm5	# %sfp, tmp1631, tmp1185
	vpcmpeqd	-12816(%rbp), %ymm10, %ymm4	# %sfp, tmp1631, tmp1188
	vpcmpeqd	%ymm10, %ymm7, %ymm7	# tmp1631, _650, tmp1171
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:1204:   return __builtin_ia32_movmskps256 ((__v8sf)__A);
	vmovmskps	%ymm5, %edi	# tmp1185,
	movq	%rdi, %r14	#,
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmi2intrin.h:71:   return __builtin_ia32_pdep_di (__X, __Y);
	pdep	%r11, %rdi, %rdi	# tmp1927, _465, tmp1193
# pipeline_avx2.c:805: /*1*/       uint64_t byte_mask1 = _pdep_u64(scalar_empty_mask1, 0x0101010101010101) * 0xFF; // (3)p1 (PDEP) -> [(3)p1 (IMUL) or (1)p06 (SAR) -> (1)p0156 (SUB)]
	movq	%rdi, %rdx	# tmp1193, tmp1198
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:1204:   return __builtin_ia32_movmskps256 ((__v8sf)__A);
	vmovmskps	%ymm4, %r8d	# tmp1188,
# pipeline_avx2.c:805: /*1*/       uint64_t byte_mask1 = _pdep_u64(scalar_empty_mask1, 0x0101010101010101) * 0xFF; // (3)p1 (PDEP) -> [(3)p1 (IMUL) or (1)p06 (SAR) -> (1)p0156 (SUB)]
	salq	$8, %rdx	#, tmp1198
	subq	%rdi, %rdx	# tmp1193, tmp1199
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:1204:   return __builtin_ia32_movmskps256 ((__v8sf)__A);
	movq	%r8, %r15	#,
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmi2intrin.h:71:   return __builtin_ia32_pdep_di (__X, __Y);
	pdep	%r11, %r8, %r8	# tmp1929, _471, tmp1200
# pipeline_avx2.c:806: /*1*/       uint64_t byte_mask2 = _pdep_u64(scalar_empty_mask2, 0x0101010101010101) * 0xFF; // (3)p1 (PDEP) -> [(3)p1 (IMUL) or (1)p06 (SAR) -> (1)p0156 (SUB)]
	movq	%r8, %rdi	# tmp1200, tmp1205
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmi2intrin.h:78:   return __builtin_ia32_pext_di (__X, __Y);
	movabsq	$506097522914230528, %r11	#, tmp1931
# pipeline_avx2.c:806: /*1*/       uint64_t byte_mask2 = _pdep_u64(scalar_empty_mask2, 0x0101010101010101) * 0xFF; // (3)p1 (PDEP) -> [(3)p1 (IMUL) or (1)p06 (SAR) -> (1)p0156 (SUB)]
	salq	$8, %rdi	#, tmp1205
	subq	%r8, %rdi	# tmp1200, tmp1206
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmi2intrin.h:78:   return __builtin_ia32_pext_di (__X, __Y);
	pext	%rdx, %r11, %r8	# tmp1199, tmp1931, tmp1215
# /usr/lib/gcc/x86_64-linux-gnu/11/include/emmintrin.h:592:   return __extension__ (__m128i)(__v2di){ __q0, __q1 };
	vmovq	%r8, %xmm8	# tmp1215, tmp1219
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:491:   return (__m256i) __builtin_ia32_pmovzxbd256 ((__v16qi)__X);
	vpmovzxbd	%xmm8, %ymm8	# tmp1219, tmp1218
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1046:   return (__m256i) __builtin_ia32_permvarsi256 ((__v8si)__X, (__v8si)__Y);
	vpermd	%ymm3, %ymm8, %ymm3	# _637, tmp1218, tmp1227
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:181:   return (__m256i) ((__v4du)__A & (__v4du)__B);
	vpand	.LC8(%rip), %ymm3, %ymm3	#, tmp1227, tmp1239
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:562:   return (__m256i) ((__v8su)__A * (__v8su)__B);
	vpmulld	.LC7(%rip), %ymm1, %ymm1	#, tmp1164, tmp1165
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:935:   *__P = __A;
	vmovdqu	%ymm3, -4160(%rbp,%rax,4)	# tmp1239, MEM[(__m256i_u * {ref-all})_52]
# pipeline_avx2.c:837: /*1*/       _mm256_storeu_si256((__m256i *)&hashed.hashes[hashed.last],packed_hashes1);
	movslq	-60(%rbp), %rax	# hashed.last, hashed.last
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:209:   return (__m256i) __builtin_ia32_pblendvb256 ((__v32qi)__X,
	vpblendvb	%ymm7, %ymm15, %ymm1, %ymm1	# tmp1171, hashes1, tmp1165, tmp1163
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:684:   return (__m256i)__builtin_ia32_pslldi256 ((__v8si)__A, __B);
	vpslld	$5, %ymm1, %ymm15	#, tmp1163, tmp1209
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:247:   return (__m256i) ((__v8si)__A == (__v8si)__B);
	vmovdqa	%ymm4, -13008(%rbp)	# tmp1188, %sfp
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:775:   return (__m256i)__builtin_ia32_psrldi256 ((__v8si)__A, __B);
	vpsrld	$27, %ymm1, %ymm4	#, tmp1163, tmp1207
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1046:   return (__m256i) __builtin_ia32_permvarsi256 ((__v8si)__X, (__v8si)__Y);
	vpermd	%ymm1, %ymm8, %ymm1	# tmp1163, tmp1218, tmp1237
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:935:   *__P = __A;
	vmovdqu	%ymm1, -2112(%rbp,%rax,4)	# tmp1237, MEM[(__m256i_u * {ref-all})_54]
# pipeline_avx2.c:838: /*1*/       hashed.last += empty_cnt1;
	movl	-60(%rbp), %eax	# hashed.last, _56
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmi2intrin.h:78:   return __builtin_ia32_pext_di (__X, __Y);
	pext	%rdi, %r11, %r8	# tmp1206, tmp1932, tmp1221
# /usr/lib/gcc/x86_64-linux-gnu/11/include/emmintrin.h:592:   return __extension__ (__m128i)(__v2di){ __q0, __q1 };
	vmovq	%r8, %xmm7	# tmp1221, tmp1225
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:491:   return (__m256i) __builtin_ia32_pmovzxbd256 ((__v16qi)__X);
	vpmovzxbd	%xmm7, %ymm7	# tmp1225, tmp1224
# pipeline_avx2.c:808: /*1*/       empty_cnt1 = __builtin_popcount(scalar_empty_mask1); // (3)p1 (POPCNT)
	popcntl	%r14d, %r14d	# tmp1189, empty_cnt1
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1046:   return (__m256i) __builtin_ia32_permvarsi256 ((__v8si)__X, (__v8si)__Y);
	vpermd	%ymm2, %ymm7, %ymm2	# _635, tmp1224, tmp1228
# pipeline_avx2.c:838: /*1*/       hashed.last += empty_cnt1;
	addl	%r14d, %eax	# empty_cnt1, _56
	movl	%eax, -60(%rbp)	# _56, hashed.last
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:181:   return (__m256i) ((__v4du)__A & (__v4du)__B);
	vpand	.LC8(%rip), %ymm2, %ymm2	#, tmp1228, tmp1258
# pipeline_avx2.c:843: /*1*/       _mm256_storeu_si256((__m256i *)&hashed.indexes[hashed.last],packed_indexes2);
	cltq
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:935:   *__P = __A;
	vmovdqu	%ymm2, -4160(%rbp,%rax,4)	# tmp1258, MEM[(__m256i_u * {ref-all})_60]
# pipeline_avx2.c:844: /*1*/       _mm256_storeu_si256((__m256i *)&hashed.hashes[hashed.last],packed_hashes2);
	movslq	-60(%rbp), %rax	# hashed.last, hashed.last
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:684:   return (__m256i)__builtin_ia32_pslldi256 ((__v8si)__A, __B);
	vpslld	$5, %ymm0, %ymm13	#, tmp1173, tmp1213
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:247:   return (__m256i) ((__v8si)__A == (__v8si)__B);
	vmovdqa	%ymm5, -12976(%rbp)	# tmp1185, %sfp
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:775:   return (__m256i)__builtin_ia32_psrldi256 ((__v8si)__A, __B);
	vpsrld	$27, %ymm0, %ymm5	#, tmp1173, tmp1211
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:1046:   return (__m256i) __builtin_ia32_permvarsi256 ((__v8si)__X, (__v8si)__Y);
	vpermd	%ymm0, %ymm7, %ymm0	# tmp1173, tmp1224, tmp1238
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:935:   *__P = __A;
	vmovdqu	%ymm0, -2112(%rbp,%rax,4)	# tmp1238, MEM[(__m256i_u * {ref-all})_62]
# pipeline_avx2.c:845: /*1*/       hashed.last += empty_cnt2;
	movl	-60(%rbp), %eax	# hashed.last, _64
# pipeline_avx2.c:809: /*1*/       empty_cnt2 = __builtin_popcount(scalar_empty_mask2); // (3)p1 (POPCNT)
	popcntl	%r15d, %r15d	# tmp1191, empty_cnt2
# pipeline_avx2.c:845: /*1*/       hashed.last += empty_cnt2;
	addl	%r15d, %eax	# empty_cnt2, _64
	movl	%eax, -60(%rbp)	# _64, hashed.last
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:576:   return (__m256i) ((__v4du)__A | (__v4du)__B);
	vpor	%ymm15, %ymm4, %ymm4	# tmp1209, tmp1207, tmp1229
	vpor	%ymm13, %ymm5, %ymm5	# tmp1213, tmp1211, tmp1233
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:915:   return (__m256i) ((__v4du)__A ^ (__v4du)__B);
	vpxor	-13040(%rbp), %ymm4, %ymm4	# %sfp, tmp1229, tmp1230
	vpxor	-12816(%rbp), %ymm5, %ymm5	# %sfp, tmp1233, tmp1234
# pipeline_avx2.c:847: /*1*/       _mm256_storeu_si256((__m256i *)&hashed.indexes[hashed.last],_mm256_setzero_si256());
	cltq
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmi2intrin.h:71:   return __builtin_ia32_pdep_di (__X, __Y);
	pdep	%rdi, %r11, %rdi	# tmp1206, tmp1935, tmp1252
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avxintrin.h:935:   *__P = __A;
	vmovdqu	%ymm9, -4160(%rbp,%rax,4)	# tmp1635, MEM[(__m256i_u * {ref-all})_66]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/emmintrin.h:592:   return __extension__ (__m128i)(__v2di){ __q0, __q1 };
	vmovq	%rdi, %xmm8	# tmp1252, tmp1256
# /usr/lib/gcc/x86_64-linux-gnu/11/include/bmi2intrin.h:71:   return __builtin_ia32_pdep_di (__X, __Y);
	pdep	%rdx, %r11, %rdx	# tmp1199, tmp1934, tmp1246
	leal	(%r15,%r14), %edi	#, tmp1616
# /usr/lib/gcc/x86_64-linux-gnu/11/include/emmintrin.h:592:   return __extension__ (__m128i)(__v2di){ __q0, __q1 };
	vmovq	%rdx, %xmm13	# tmp1246, tmp1250
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:562:   return (__m256i) ((__v8su)__A * (__v8su)__B);
	vpmulld	.LC7(%rip), %ymm4, %ymm15	#, tmp1230, hashes1
	movl	%edi, -12816(%rbp)	# tmp1616, %sfp
# pipeline_avx2.c:850: /*2*/    uint32_t hashed_valid_cnt = hashed.last - hashed.first;
	movl	-60(%rbp), %eax	# hashed.last, count
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:491:   return (__m256i) __builtin_ia32_pmovzxbd256 ((__v16qi)__X);
	vpmovzxbd	%xmm13, %ymm13	# tmp1250, unpack_scheme1
	vpmovzxbd	%xmm8, %ymm8	# tmp1256, unpack_scheme2
# /usr/lib/gcc/x86_64-linux-gnu/11/include/avx2intrin.h:562:   return (__m256i) ((__v8su)__A * (__v8su)__B);
	vpmulld	.LC7(%rip), %ymm5, %ymm4	#, tmp1234, hashes2