	vmovups	(%rdx,%r11), %xmm4	# MEM[(__m128_u * {ref-all})_130 + _12 * 1], MEM[(__m128_u * {ref-all})_130 + _12 * 1]
	vmovups	(%rdx), %xmm0	# MEM[(__m128_u * {ref-all})_130], MEM[(__m128_u * {ref-all})_130]
	vmovups	(%rdx,%r8), %xmm2	# MEM[(__m128_u * {ref-all})_130 + _4 * 1], MEM[(__m128_u * {ref-all})_130 + _4 * 1]
	vmovups	(%rdx,%r10), %xmm7	# MEM[(__m128_u * {ref-all})_130 + _8 * 1], MEM[(__m128_u * {ref-all})_130 + _8 * 1]
	vmovups	(%rdx,%rsi), %xmm6	# MEM[(__m128_u * {ref-all})_130 + _18 * 1], MEM[(__m128_u * {ref-all})_130 + _18 * 1]
	vmovups	(%rdx,%rdi), %xmm1	# MEM[(__m128_u * {ref-all})_130 + _14 * 1], MEM[(__m128_u * {ref-all})_130 + _14 * 1]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:765:   return (__m128) __builtin_ia32_unpcklps ((__v4sf)__A, (__v4sf)__B);
	vunpcklps	%xmm4, %xmm2, %xmm5	# MEM[(__m128_u * {ref-all})_130 + _12 * 1], MEM[(__m128_u * {ref-all})_130 + _4 * 1], tmp175
	vunpcklps	%xmm7, %xmm0, %xmm3	# MEM[(__m128_u * {ref-all})_130 + _8 * 1], MEM[(__m128_u * {ref-all})_130], tmp174
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:758:   return (__m128) __builtin_ia32_unpckhps ((__v4sf)__A, (__v4sf)__B);
	vunpckhps	%xmm4, %xmm2, %xmm2	# MEM[(__m128_u * {ref-all})_130 + _12 * 1], MEM[(__m128_u * {ref-all})_130 + _4 * 1], tmp177
	vunpckhps	%xmm7, %xmm0, %xmm0	# MEM[(__m128_u * {ref-all})_130 + _8 * 1], MEM[(__m128_u * {ref-all})_130], tmp176
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:765:   return (__m128) __builtin_ia32_unpcklps ((__v4sf)__A, (__v4sf)__B);
	vunpcklps	%xmm6, %xmm1, %xmm4	# MEM[(__m128_u * {ref-all})_130 + _18 * 1], MEM[(__m128_u * {ref-all})_130 + _14 * 1], tmp178
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:758:   return (__m128) __builtin_ia32_unpckhps ((__v4sf)__A, (__v4sf)__B);
	vunpckhps	%xmm6, %xmm1, %xmm1	# MEM[(__m128_u * {ref-all})_130 + _18 * 1], MEM[(__m128_u * {ref-all})_130 + _14 * 1], tmp179
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:765:   return (__m128) __builtin_ia32_unpcklps ((__v4sf)__A, (__v4sf)__B);
	vunpcklps	%xmm5, %xmm3, %xmm6	# tmp175, tmp174, tmp180
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:758:   return (__m128) __builtin_ia32_unpckhps ((__v4sf)__A, (__v4sf)__B);
	vunpckhps	%xmm5, %xmm3, %xmm3	# tmp175, tmp174, tmp182
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:983:   *(__m128_u *)__P = __A;
	vmovups	%xmm3, 8(%rax)	# tmp182, MEM[(__m128_u * {ref-all})_124 + 8B]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:765:   return (__m128) __builtin_ia32_unpcklps ((__v4sf)__A, (__v4sf)__B);
	vunpcklps	%xmm2, %xmm0, %xmm3	# tmp177, tmp176, tmp185
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:758:   return (__m128) __builtin_ia32_unpckhps ((__v4sf)__A, (__v4sf)__B);
	vunpckhps	%xmm2, %xmm0, %xmm0	# tmp177, tmp176, tmp188
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:983:   *(__m128_u *)__P = __A;
	vmovups	%xmm6, -16(%rax)	# tmp180, MEM[(__m128_u * {ref-all})_124 + -16B]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:809:   __builtin_ia32_storelps ((__v2sf *)__P, (__v4sf)__A);
	vmovlps	%xmm4, (%rax)	# tmp178,* ivtmp.118
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:780:   __builtin_ia32_storehps ((__v2sf *)__P, (__v4sf)__A);
	vmovhps	%xmm4, 24(%rax)	# tmp178,
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:983:   *(__m128_u *)__P = __A;
	vmovups	%xmm3, 32(%rax)	# tmp185, MEM[(__m128_u * {ref-all})_124 + 32B]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:809:   __builtin_ia32_storelps ((__v2sf *)__P, (__v4sf)__A);
	vmovlps	%xmm1, 48(%rax)	# tmp179,
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:983:   *(__m128_u *)__P = __A;
	vmovups	%xmm0, 56(%rax)	# tmp188, MEM[(__m128_u * {ref-all})_124 + 56B]
# /usr/lib/gcc/x86_64-linux-gnu/11/include/xmmintrin.h:780:   __builtin_ia32_storehps ((__v2sf *)__P, (__v4sf)__A);
	vmovhps	%xmm1, 72(%rax)	# tmp179,