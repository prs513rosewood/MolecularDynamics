---
layout: default
title: " 06"
parent: Lecture
date: 2022-06-15
categories: lecture
author: Lars Pastewka
nav_order: 06
---
---

<h2 class='chapterHead' id='parallel-computers-and-the-message-passing-interface'><span class='titlemark'>Chapter 6</span><br />
<a id='x1-10006'></a>Parallel computers and the Message Passing Interface</h2>
<div class='framedenv' id='shaded*-1'><!--  l. 3  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Context:</span></span> This chapter sets the stage for discussing parallelization of the molecular dynamics simulation method introduced in the previous chapters. We first need to talk about parallel hardware architectures and how to program for them. The specific programming model that we will employ is known under the term <span class='cmti-12'>Single Program Multiple Data</span>. The Message Passing Interface (MPI) is a library that
facilitates programming for massively parallel machines under this programming model.</p>
</div>
<h3 class='sectionHead' id='parallel-hardware-architectures'><span class='titlemark'>6.1</span> <a id='x1-20006.1'></a>Parallel hardware architectures</h3>
<!--  l. 9  -->
<p class='noindent'>Parallel hardware has become ubiquitous over the past decade. Most central processing units (CPUs) in computers, phones or other hardware have multiple cores that can execute instructions in parallel. Massively parallel computing systems combine multiple CPUs into nodes that share a common memory. These nodes are then combined into the full compute system through a network interconnect.</p>
<!--  l. 11  -->
<p class='indent'>Parallel architecture are often hierachical and have parallelization at different levels. Notable is vectorization at the core-level, share memory parallelization for multicore architectures and distributed memory parallelization for large computing systems that communicate via an interconnect (a network connection).</p>
<!--  l. 13  -->
<p class='indent'><a class='url' href='https://uni-freiburg.cloud.panopto.eu/Panopto/Pages/Embed.aspx?id=6439ba0b-8da2-4cb6-94da-ab9d009f062e'><span class='cmtt-12'>https://uni-freiburg.cloud.panopto.eu/Panopto/Pages/Embed.aspx?id=6439ba0b-8da2-4cb6-94da-ab9d009f062e</span></a></p>
<!--  l. 15  -->
<p class='noindent'></p>
<h3 class='sectionHead' id='scaling-consideration'><span class='titlemark'>6.2</span> <a id='x1-30006.2'></a>Scaling consideration</h3>
<!--  l. 17  -->
<p class='noindent'>Software that runs on parallel computers needs to scale. Scaling describes how the time to returning the result changes as the number of available compute units (cores) changes. The simplest model for scaling assumes that our code can be divided into a fraction \(f_s\) that needs to be executed on a single core while a fraction \(f_p\) scales perfectly, i.e. its execute time is \(\propto 1/p\) where \(p\) is the number of available processes or cores. (Note that \(f_s+f_p=1\) since they
are fractions.) This leads to Amdahl’s law that describes the speedup \(S\) as a function of \(p\): \begin {equation} S = p f_p + f_s p \end {equation}</p>
<!--  l. 22  -->
<p class='indent'><a class='url' href='https://uni-freiburg.cloud.panopto.eu/Panopto/Pages/Embed.aspx?id=95d5d79d-4259-4865-af14-ab9d0099e7cb'><span class='cmtt-12'>https://uni-freiburg.cloud.panopto.eu/Panopto/Pages/Embed.aspx?id=95d5d79d-4259-4865-af14-ab9d0099e7cb</span></a></p>
<!--  l. 24  -->
<p class='noindent'></p>
<h3 class='sectionHead' id='programming-model'><span class='titlemark'>6.3</span> <a id='x1-40006.3'></a>Programming model</h3>
<!--  l. 26  -->
<p class='noindent'>The Message Passing Interface (MPI) is an application programming interface (API) for distributed memory parallelization. (A code parallelized with MPI also works on shared memory machines!) The programming model underlying MPI is called single program multiple data (SPMD): The identical program is executed multiple times but operates on different datums.</p>
<!--  l. 28  -->
<p class='indent'><a class='url' href='https://uni-freiburg.cloud.panopto.eu/Panopto/Pages/Embed.aspx?id=88d86075-f904-4e83-bae6-ab9d00a3e197'><span class='cmtt-12'>https://uni-freiburg.cloud.panopto.eu/Panopto/Pages/Embed.aspx?id=88d86075-f904-4e83-bae6-ab9d00a3e197</span></a></p>
<!--  l. 30  -->
<p class='noindent'></p>
<h4 class='subsectionHead' id='example-montecarlo-estimate-of-the-number-'><span class='titlemark'>6.3.1</span> <a id='x1-50006.3.1'></a>Example: Monte-Carlo estimate of the number \(\pi \)</h4>
<!--  l. 32  -->
<p class='noindent'>As the simplest example of a parallelization, we consider a Monte-Carlo estimate of the number \(\pi \).</p>
<!--  l. 34  -->
<p class='indent'><a class='url' href='https://uni-freiburg.cloud.panopto.eu/Panopto/Pages/Embed.aspx?id=18ce5d9a-50cf-4834-8a22-aba100bf31cb'><span class='cmtt-12'>https://uni-freiburg.cloud.panopto.eu/Panopto/Pages/Embed.aspx?id=18ce5d9a-50cf-4834-8a22-aba100bf31cb</span></a></p>
<h2 class='likechapterHead' id='bibliography'><a id='x1-60006.3.1'></a>Bibliography</h2>
<div class='thebibliography'>
<p class='bibitem'><span class='biblabel'><a id='Xberendsen_molecular_1984'></a><span class='bibsp'>   </span></span>H. J. C. Berendsen, J. P. M. Postma, W. F. van Gunsteren, A. DiNola, and J. R. Haak. Molecular dynamics with coupling to an external bath. <span class='cmti-12'>J. Chem. Phys.</span>, 81(8):3684–3690, 1984. URL <a class='url' href='https://doi.org/10.1063/1.448118'><span class='cmtt-12'>https://doi.org/10.1063/1.448118</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xcleri_tight-binding_1993'></a><span class='bibsp'>   </span></span>F. Cleri and V. Rosato. Tight-binding potentials for transition metals and alloys. <span class='cmti-12'>Phys. Rev. B</span>, 48(1):22–33, 1993. URL <a class='url' href='https://doi.org/10.1103/PhysRevB.48.22'><span class='cmtt-12'>https://doi.org/10.1103/PhysRevB.48.22</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xdaw_semiempirical_1983'></a><span class='bibsp'>   </span></span>M. S. Daw and M. I. Baskes. Semiempirical, quantum mechanical calculation of hydrogen embrittlement in metals. <span class='cmti-12'>Phys. Rev. Lett.</span>, 50(17):1285–1288, 1983. URL <a class='url' href='https://doi.org/10.1103/PhysRevLett.50.1285'><span class='cmtt-12'>https://doi.org/10.1103/PhysRevLett.50.1285</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='XEckhardt2013-oh'></a><span class='bibsp'>   </span></span>W. Eckhardt, A. Heinecke, R. Bader, M. Brehm, N. Hammer, H. Huber, H.-G. Kleinhenz, J. Vrabec, H. Hasse, M. Horsch, M. Bernreuther, C. W. Glass, C. Niethammer, A. Bode, and H.-J. Bungartz. 591 TFLOPS multi-trillion particles simulation on SuperMUC. In <span class='cmti-12'>Supercomputing</span>, pages 1–12. Springer
Berlin Heidelberg, 2013. URL <a class='url' href='https://doi.org/10.1007/978-3-642-38750-0_1'><span class='cmtt-12'>https://doi.org/10.1007/978-3-642-38750-0_1</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xercolessi_interatomic_1994'></a><span class='bibsp'>   </span></span>F. Ercolessi and J. B. Adams. Interatomic Potentials from First-Principles Calculations: The Force-Matching Method. <span class='cmti-12'>EPL</span>, 26(8): 583–588, 1994. URL <a class='url' href='https://doi.org/10.1209/0295-5075/26/8/005'><span class='cmtt-12'>https://doi.org/10.1209/0295-5075/26/8/005</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xferrante_diatomic_1983'></a><span class='bibsp'>   </span></span>J. Ferrante, J. Smith, and J. Rose. Diatomic Molecules and Metallic Adhesion, Cohesion, and Chemisorption: A Single Binding-Energy Relation. <span class='cmti-12'>Phys.</span> <span class='cmti-12'>Rev. Lett.</span>, 50(18):1385–1386, 1983. doi: 10.1103/PhysRevLett.50.1385. URL <a class='url' href='http://www.ncbi.nlm.nih.gov/pubmed/23357448'><span class='cmtt-12'>http://www.ncbi.nlm.nih.gov/pubmed/23357448</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='XFeynman1964Book'></a><span class='bibsp'>   </span></span>R. P. Feynman, R. B. Leighton, and M. Sands. <span class='cmti-12'>The Feynman Lectures</span> <span class='cmti-12'>on Physics</span>. Addison-Wesley, New York, 1964.</p>
<p class='bibitem'><span class='biblabel'><a id='Xfinnis_simple_1984'></a><span class='bibsp'>   </span></span>M. W. Finnis and J. E. Sinclair. A simple empirical N-body potential for transition metals. <span class='cmti-12'>Phil. Mag. A</span>, 50(1):45–55, 1984. URL <a class='url' href='https://doi.org/10.1080/01418618408244210'><span class='cmtt-12'>https://doi.org/10.1080/01418618408244210</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xfoiles_embedded-atom-method_1986'></a><span class='bibsp'>   </span></span>S. M. Foiles, M. I. Baskes, and M. S. Daw. Embedded-atom-method functions for the fcc metals Cu, Ag, Au, Ni, Pd, Pt, and their alloys. <span class='cmti-12'>Phys. Rev. B</span>, 33(12):7983–7991, 1986. URL <a class='url' href='https://doi.org/10.1103/PhysRevB.33.7983'><span class='cmtt-12'>https://doi.org/10.1103/PhysRevB.33.7983</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xgrochola_fitting_2005'></a><span class='bibsp'>   </span></span>G. Grochola, S. P. Russo, and I. K. Snook. On fitting a gold embedded atom method potential using the force matching method. <span class='cmti-12'>J. Chem. Phys.</span>, 123(20):204719, 2005. URL <a class='url' href='https://doi.org/10.1063/1.2124667'><span class='cmtt-12'>https://doi.org/10.1063/1.2124667</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xgupta_lattice_1981'></a><span class='bibsp'>   </span></span>R. P. Gupta. Lattice relaxation at a metal surface. <span class='cmti-12'>Phys. Rev. B</span>, 23(12): 6265–6270, 1981. URL <a class='url' href='https://doi.org/10.1103/PhysRevB.23.6265'><span class='cmtt-12'>https://doi.org/10.1103/PhysRevB.23.6265</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xrose_universal_1984'></a><span class='bibsp'>   </span></span>J. Rose, J. Smith, F. Guinea, and J. Ferrante. Universal features of the equation of state of metals. <span class='cmti-12'>Phys. Rev. B</span>, 29(6):2963–2969, 1984. URL <a class='url' href='https://doi.org/10.1103/PhysRevB.29.2963'><span class='cmtt-12'>https://doi.org/10.1103/PhysRevB.29.2963</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xsukhomlinov_constraints_2016'></a><span class='bibsp'>   </span></span>S. V. Sukhomlinov and M. H. Müser. Constraints on phase stability, defect energies, and elastic constants of metals described by EAM-type potentials. <span class='cmti-12'>J. Phys.: Condens. Matter</span>, 28(39):395701, 2016. URL <a class='url' href='https://doi.org/10.1088/0953-8984/28/39/395701'><span class='cmtt-12'>https://doi.org/10.1088/0953-8984/28/39/395701</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='XTchipev2019-fl'></a><span class='bibsp'>   </span></span>N. Tchipev, S. Seckler, M. Heinen, J. Vrabec, F. Gratl, M. Horsch, M. Bernreuther, C. W. Glass, C. Niethammer, N. Hammer, B. Krischok, M. Resch, D. Kranzlmüller, H. Hasse, H.-J. Bungartz, and P. Neumann. TweTriS: Twenty trillion-atom simulation. <span class='cmti-12'>Int. J. High Perform. Comput. Appl.</span>,
33(5):838–854, Sept. 2019. URL <a class='url' href='https://doi.org/10.1177/1094342018819741'><span class='cmtt-12'>https://doi.org/10.1177/1094342018819741</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='Xvitek_pair_1996'></a><span class='bibsp'>   </span></span>V. Vitek. Pair potentials in atomistic computer simulations. <span class='cmti-12'>MRS Bull.</span>, 21(2):20–23, 1996. URL <a class='url' href='https://doi.org/10.1557/S088376940004625X'><span class='cmtt-12'>https://doi.org/10.1557/S088376940004625X</span></a>.</p>
</div>
