	vmovdqa	-12816(%rbp), %ymm5	# %sfp, _589
	vpmovzxdq	%xmm3, %ymm1	# MEM[(const __m256i_u * {ref-all})_124],
	vpaddq	%ymm5, %ymm1, %ymm1	# _589, _748, _744

	vmovq	%xmm1, %rax	# tmp1364, hstate_p
	movq	88(%rax), %rax	# hstate_p_1090->next_chain_ref, hstate_p_1090->next_chain_ref
	vpermq	$57, %ymm1, %ymm2	#, _744, tmp1361
	prefetcht2	(%rax)	# hstate_p_1090->next_chain_ref
	vmovq	%xmm2, %rax	# tmp1370, hstate_p
	movq	88(%rax), %rax	# hstate_p_1098->next_chain_ref, hstate_p_1098->next_chain_ref
	vpermq	$57, %ymm2, %ymm1	#, tmp1361, tmp1367
	vpermq	$57, %ymm1, %ymm2	#, tmp1367, tmp1373
	prefetcht2	(%rax)	# hstate_p_1098->next_chain_ref

	vmovq	%xmm1, %rax	# tmp1376, hstate_p
	vpmovzxdq	%xmm0, %ymm1	# MEM[(const __m256i_u * {ref-all})_145],
	movq	88(%rax), %rax	# hstate_p_1106->next_chain_ref, hstate_p_1106->next_chain_ref

	vpaddq	%ymm5, %ymm1, %ymm1	# _589, _757, _753
	vmovq	%xmm1, %rdx	# tmp1389, dstate_p
	prefetcht2	(%rax)	# hstate_p_1106->next_chain_ref

	vmovq	%xmm2, %rax	# tmp1382, hstate_p
	movq	88(%rax), %rax	# hstate_p_1114->next_chain_ref, hstate_p_1114->next_chain_ref
	prefetcht2	(%rax)	# hstate_p_1114->next_chain_ref
