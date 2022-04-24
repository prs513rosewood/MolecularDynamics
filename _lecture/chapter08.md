---
layout: default
title: "Chapter 08"
parent: Lecture
date: 2022-04-24
categories: lecture
author: Lars Pastewka
nav_order: 08
---

<h2 class='chapterHead' id='periodicity-and-pressure'><span class='titlemark'>Chapter 8</span><br />
<a id='x1-10008'></a>Periodicity and pressure</h2>
<div class='framedenv' id='shaded*-1'><!--  l. 3  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Context:</span></span> Now that we have introduced the notion of the simulation domain, we can introduce <span class='cmti-12'>periodicity</span>. In a periodic domain, atoms on the right interact with atoms on the left. Periodic domains are commonly used to represent bulk solid or fluid materials and eliminate the effect of interfaces or surfaces. They are sometimes referred to as <span class='cmti-12'>representative volume elements
(RVEs)</span>. The state of the RVE depends on its volume (or the full domain matrix) and we can introduce the conjugate variable, the pressure (or stress tensor).</p>
</div>
<h3 class='sectionHead' id='periodicity'><span class='titlemark'>8.1</span> <a id='x1-20008.1'></a>Periodicity</h3>
<!--  l. 9  -->
<p class='noindent'>All energy expressions here are written as \(E_\text {pot}(\{ {\v {r}}_{i} \})\). If there is no periodic interaction across the domain boundaries, the energies depends on positions only. For periodic interactions, they depend explicity on the domain vectors \(\v {a}_{1}\), \(\v {a}_{2}\) and \(\v {a}_{3}\) or the corresponding matrix \(\t {h}\): \(E_\text {pot} = E_\text {pot}(\t {h};\{ \v {s}_{i} \})\), where we have expressed the positions in the respective scaled coordinates.</p>
<!--  l. 14  -->
<p class='indent'>Periodicity is implicitly contained in the way the potential is written. E.g. for a pair potential, \begin {equation} E_\text {pot}( \{ \vec {r}_{i} \}) = \frac {1}{2} \sum _{i=1}^N \sum _{j=1}^N \phi (r_{ij}) = \sum _{i &lt; j} \phi (r_{ij}), \label {eq:epotpair2} \end {equation} the energy depends only on relative positions \(\v {r}_{ij}\). This distance vector contains the information of the simulation domain implicitly. All potential energy expression must be a function of relative
positions, never of absolute positions, since this would violate momentum conservation (Newton’s second law). Note that in terms of the matrix \(\t {h}\) and the scaled positions, the potential energy becomes \begin {equation} E_\text {pot}(\t {h};\{ \v {s}_{i} \}) = \sum _{i &lt; j} \phi (|\t {h}\cdot \v {s}_{ij}|), \end {equation} where \(\v {s}_{ij}=\v {s}_i - \v {s}_j\) is the scaled distance between the atoms \(i\) and \(j\).</p>
<!--  l. 25  -->
<p class='noindent'></p>
<h3 class='sectionHead' id='ghost-atoms'><span class='titlemark'>8.2</span> <a id='x1-30008.2'></a>Ghost atoms</h3>
<!--  l. 27  -->
<p class='noindent'>There are different ways to realize periodic domains in MD simulation codes. A common way is to incorporate periodicity into the neighbor list, which is then build to include neighbors across domain boundaries with the correct distance vector \(\v {r}_{ij}\). The potential energy of the system is then given by Eq. \eqref{eq:epotpair2}.</p>
<!--  l. 29  -->
<p class='indent'>An alternative is to construct a supercell of the domain, i.e. replicate the domain such that the repeating periodic image is explicitly present. In practice, this is equivalent to creating a region of ghost atoms around the domain and this is naturally incorporated into the portion of the code handling the domain decomposition (that was described in the previous chapter). In this case, the potential energy is given by \begin {equation} E_\text {pot}( \{ \vec {r}_{i} \}) = \frac {1}{2}
\sum _{i=1}^N \sum _{j=1}^{N + N_\text {G}} \phi (r_{ij}), \end {equation} where it is important to realize that the sum over \(i\) runs over all atoms in the domain, while the sum over \(j\) runs over the \(N\) domain atoms as well as the \(N_\text {G}\) ghost atoms with index \(j\in [N+1,N_\text {G}]\). This strategy is for example found in the widely used MD code <span class='cmcsc-10x-x-120'><span class='small-caps'>lammps</span></span> (<a href='#Xplimpton_fast_1995'>Plimpton</a>, <a href='#Xplimpton_fast_1995'>1995</a>; <a href='#XThompson2022-qg'>Thompson et al.</a>, <a href='#XThompson2022-qg'>2022</a>).</p>
<!--  l. 35  -->
<p class='noindent'></p>
<h3 class='sectionHead' id='pressure-and-stress'><span class='titlemark'>8.3</span> <a id='x1-40008.3'></a>Pressure and stress</h3>
<!--  l. 37  -->
<p class='noindent'>For a periodic domain (an RVE) we can ask what the pressure of the system is. From a thermodynamic perspective, the (potential energy contribution to the) pressure is given by \begin {equation} P = -\frac {\partial E_\text {pot}}{\partial V}, \end {equation} where \(V=\det \t {h}\) is the volume of the domain. This expression is only valid at zero temperature; at finite temperature we need to use the free energy rather than the potential energy and this yields an additional kinetic
contribution to the pressure.</p>
<!--  l. 43  -->
<p class='indent'>When working with solids, we are often interested in the full stress tensor \(\t {\sigma }\) of the system. Let us assume our RVE undergoes a deformation. This means the domain matrix is taken from \(\t {h}\) to \(\t {h}^\prime = \t {F}\cdot \t {h}\) where \(\t {F}\) is called the <span class='cmti-12'>deformation gradient</span>. The Cauchy stress is then given by \begin {equation} \t {\sigma } = \frac {1}{V} \left . \frac {\partial E_\text {pot}(\t {h}^\prime ;\{ \v {s}_{i}
\})}{\partial \t {F}} \right |_{\t {F}=\t {1}}, \end {equation} where the derivative with respect to the deformation gradient \(\t {F}\) is taken component-wise.</p>
<!--  l. 49  -->
<p class='indent'>Evaluating the stress for Eq. \eqref{eq:epotpair2} yields \begin {equation} \t {\sigma } = \frac {1}{V} \sum _{i &lt; j} \left .\frac {\partial \phi (|\t {F}\cdot \v {r}_{ij}|)}{\partial \t {F}} \right |_{\t {F}=\t {1}} = \frac {1}{V} \sum _{i &lt; j} \frac {\partial \phi }{\partial r_{ij}} \v {r}_{ij} \otimes \v {r}_{ij} \label {eq:stress1} \end {equation} where \(\otimes \) is the outer product, \([\v {a}\otimes \v {b}]_{ij} = a_i b_j\). Equation Eq. \eqref{eq:stress1} can be
directly used to compute the stress of a pair-potential in molecular dynamics, and similar expression can derived for other potentials such as EAM.</p>
<!--  l. 58  -->
<p class='noindent'></p>
<h3 class='sectionHead' id='stress-and-ghost-atoms'><span class='titlemark'>8.4</span> <a id='x1-50008.4'></a>Stress and ghost atoms</h3>
<!--  l. 60  -->
<p class='noindent'>In the presence of ghost atoms, there is a simpler way to compute the stress in the simulation cell. While an expression like Eq. \eqref{eq:stress1} needs to be derived for every functional form of a potential, this strategy is independent of the functional form of the potential.</p>
<!--  l. 62  -->
<p class='indent'>The idea is to use the forces on the ghost atoms that enclose the simulation domain to compute the stress. The relevant expression can be derived from the conservation of the moment of inertia. (The moment of inertia is only conserved for a <span class='cmti-12'>nonperiodic</span> system - which is why this method is only applicable to supercells!) Taking the derivative of the moment of inertia \(I=\sum _i m_i r_i^2\) yields \begin {equation} \frac {1}{2} \frac {dI}{dt} = \sum _i m_i \v
{v}_i \cdot \v {r}_i \end {equation} The second derivative then becomes \begin {equation} \frac {1}{2} \frac {d^2I}{dt^2} = \sum _i (\v {f}_i \cdot \v {r}_i + m_i v_i^2) = 2E_\text {kin} + \sum _i \v {f}_i \cdot \v {r}_i \equiv 0 \label {eq:ddI} \end {equation} which has to be zero (because \(I\) is a constant of motion).</p>
<!--  l. 73  -->
<p class='indent'>Since our simulation domain is enclosed by ghost atoms, the forces \(\v {f}_i\) have a contribution from these ghosts (the container walls). Hence \(\v {f}_i = \v {f}_i^\text {domain} + \v {f}_i^\text {G}\). From Eq. \eqref{eq:ddI} we get \(\sum _i \v {f}_i^\text {G} \cdot \v {r}_i = -2E_\text {kin} - \sum _i \v {f}_i^\text {domain} \cdot \v {r}_i\). Now \(\v {f}_i^\text {G}\) can be related to the external pressure. By virtue of Newton’s third law (for every action there is an equal
and opposite reaction), the forces \(\v {f}_i^\text {G}\) (with \(i\in [1,N]\)) need to be exactly balanced by the forces \(\v {f}_i\) (with \(i\in [N+1,N_\text {G}]\)) on the <span class='cmti-12'>ghost atoms themselves</span>.</p>
<!--  l. 76  -->
<p class='indent'>Let’s assume that the particles that feel a wall force are located infinitely close to the wall itself (hard-wall assumption). If we now have a container with its <span class='cmti-12'>origin at one corner of the box</span>, then \(\sum _i \v {f}_i^\text {ext} \cdot \v {z}_i = L_z \sum _i \v {f}_i^\text {ext} = L_z (-PL_xL_y)\) because \(\v {z}_i\) is located at the wall, etc., or taking \(x\)-, \(y\)- and \(z\)-components, \(\sum _i \v {f}_i^\text {ext} \cdot \v {r}_i = -3PL_xL_yL_z\).
This means \begin {equation} \label {eqn: virial} PV = \frac {2}{3} E_\text {kin} + \frac {1}{3} \sum _i \v {f}_i^\text {int} \cdot \v {r}_i = NkT + \frac {1}{3} \sum _i \v {f}_i^\text {int} \cdot \v {r}_i = NkT + W \end {equation} Eq. \eqref{eqn: virial} is called the virial theorem. This expression is valid for non-periodic systems only! The quantity \(W\) is called the virial.</p>
<h2 class='likechapterHead' id='bibliography'><a id='x1-60008.4'></a>Bibliography</h2>
<div class='thebibliography'>
<p class='bibitem'><span class='biblabel'><a id='Xplimpton_fast_1995'></a><span class='bibsp'>   </span></span>S. Plimpton. Fast parallel algorithms for short-range molecular dynamics. <span class='cmti-12'>J. Comput. Phys.</span>, 117(1):1–19, 1995. URL <a class='url' href='https://doi.org/10.1006/jcph.1995.1039'><span class='cmtt-12'>https://doi.org/10.1006/jcph.1995.1039</span></a>.</p>
<p class='bibitem'><span class='biblabel'><a id='XThompson2022-qg'></a><span class='bibsp'>   </span></span>A. P. Thompson, H. M. Aktulga, R. Berger, D. S. Bolintineanu, W. M. Brown, P. S. Crozier, P. J. in <span class='tcrm-1200'>'</span>t Veld, A. Kohlmeyer, S. G. Moore, T. D. Nguyen, R. Shan, M. J. Stevens, J. Tranchida, C. Trott, and S. J. Plimpton. LAMMPS - a flexible simulation tool for particle-based
materials modeling at the atomic, meso, and continuum scales. <span class='cmti-12'>Comput.</span> <span class='cmti-12'>Phys. Comm.</span>, 271:108171, 2022. doi: 10.1016/j.cpc.2021.108171.</p>
</div>
