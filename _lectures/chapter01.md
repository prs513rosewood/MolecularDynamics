---
layout: default
title: "Chapter 01"
parent: Lectures
date: 2021-04-22
categories: lecture
author: Lars Pastewka
nav_order: 01
---

<h2 class='chapterHead'><span class='titlemark'>Chapter 2</span><br />
<a id='x1-10002'></a>Introduction</h2>
<div class='framedenv' id='shaded*-1'><!--  l. 4  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Context:</span></span> We start by introducing the concept of the potential energy and the interatomic force. Those are the central ingredients to the molecular dynamics simulation method.</p>
</div>
<h3 class='sectionHead'><span class='titlemark'>2.1</span> <a id='x1-20002.1'></a>Structure of matter at the atomic scale</h3>
<!--  l. 10  -->
<p class='noindent'>All matter is build out of quark and leptons, or perhaps even smaller particles, but for the sake of modeling the real material world the atom is the fundamental unit. Atoms can be described by nuclei and electrons or through “coarse-grained” models that ignore the fact that there are electrons. Both types of models are useful for describing materials, and the latter ones will be extensively used in this class.</p>
<!--  l. 12  -->
<p class='indent'>Atoms in solids can arrange in different configurations that are called crystals when there is long-ranged order or glasses when there is not. (All solid matter typically has short-ranged order that is determined by the chemical bonds between atoms.) Atoms in solids are immobile and self-diffusion is limited. Conversely, liquids and gases are disordered (like glasses) but have mobile constituent atoms. Macroscopic object typically contain a lot of atoms – on the order of Avogadro’s
constant \(N_A\approx 6\times 10^{23}\). The atomic-scale simulation techniques discussed in this class can at the time of this writing (2020) treat on order of \(\sim 10^6\) atoms, \(10^8-10^9\) if you use the biggest computers available to us. Of course, this boundary is pushed towards larger systems as computer technology evolves.</p>
<!--  l. 15  -->
<p class='indent'>We can nowadays even observe matter at atomic scales and “see” individual atoms. The <a href='https://www.sfb-transregio103.de/'>collaborative research center 103</a> has produced an extremely instructive video on the structure of specific type of alloys, dubbed “superalloy”, that is used in e.g. turbine blades. Enjoy the ride from the blade to the atom. This class is about modeling matter at the smallest scales that you see in this video.</p>
<!--  l. 17  -->
<p class='indent'><a href='https://www.youtube.com/embed/wYHch5QIWTQ' class='url'><span class='cmtt-12'>https://www.youtube.com/embed/wYHch5QIWTQ</span></a></p>
<!--  l. 19  -->
<p class='noindent'></p>
<h3 class='sectionHead'><span class='titlemark'>2.2</span> <a id='x1-30002.2'></a>Interatomic forces and the potential energy</h3>
<!--  l. 21  -->
<p class='noindent'>Atoms interact via forces. As Feynman put it in his famous lectures on physics, the fundamental truth about man’s understanding of the physical world is “that all things are made of atoms – little particles that move around in perpetual motion, attracting each other when they are a little distance apart, but repelling upon being squeezed into one another”. Indeed this is the essence of the molecular dynamics simulation method.</p>
<!--  l. 23  -->
<p class='indent'>As the simplest example why atoms attract each other, let us consider the example of simple salt, e.g. Na-Cl that we all have sitting in our kitchen. Na-Cl in its solid form is an ionic crystal. Na atoms have approximately a charge of \(q_{\text{Na}}=+1|e|\), where \(e\) is the electron charge, and Cl atoms have a charge of approximately \(q_{\text{Na}}=-1|e|\). The Coulomb interaction between these atoms is a fundamental force of nature. Basic physical principles tell us, that the
interaction energy between a Na and a Cl atom is given by \begin{equation} V_{\text{Coulomb}}(r;q_{\text{Na}},q_{\text{Cl}}) = \frac{1}{4\pi \varepsilon _0} \frac{q_{\text{Na}} q_{\text{Cl}}}{r}. \end{equation} We also know that this energy is pair-wise additive, allowing us to write down the Coulomb interaction energy for Na-Cl consisting of \(N\) atoms, \begin{equation} E_{\text{Coulomb}}(\{\vec{r}_i\}) = \sum _{i=1}^N \sum _{j=i+1}^N V_{\text{Coulomb}}(r_{ij};q_i, q_j) = \frac{1}{4\pi \varepsilon _0}
\sum _{i=1}^N \sum _{j=i+1}^N \frac{q_i q_j}{r_{ij}} \label{eqn:coulomb} \end{equation} where \(q_i\) is the charge on atom \(i\) and \(r_{ij}=|\vec{r}_i - \vec{r}_j|\) the distance between atom \(i\) and \(j\). Note that we have introduced — in passing — a central quantity of the molecular dynamics method, the atomic positions \(\vec{r}_i\) and Eq. \eqref{eqn:coulomb} indicates that the interaction energy depends on the positions of all atoms.</p>
<!--  l. 34  -->
<p class='indent'>The Coulomb interaction has a singularity at \(r\to 0\). The attractive force between opposite charges becomes infinitely large. The salt crystal does not collapse because atoms are, as Feynman puts it, “repelling upon being squeezed into one another”. While the attraction between our Na and Cl atoms are described by a fundamental force of nature, it is more difficult to understand the origin of this repulsion. Hand-wavingly, it goes back to the fact that electrons are Fermions and
electrons from the electron shells of Na and Cl therefore cannot exist at the same point in space (and the same spin state). This is the Pauli exclusion principle and the resulting repulsive force is called Pauli repulsion.</p>
<!--  l. 36  -->
<p class='indent'>Different models for the Pauli repulsion exist. While the Coulomb interaction is a fundamental force of nature, these models are approximations to the true quantum physics that is the origin of the repulsive form. Two common forms are exponential repulsion, \begin{equation} E_{\text{rep,exp}}(\{\vec{r}_i\}) = \sum _{i=1}^N \sum _{j=i+1}^N A e^{-r/\rho }, \end{equation} or an algebraic repulsion of the form \begin{equation} E_{\text{rep,12}}(\{\vec{r}_i\}) = \sum _{i=1}^N \sum _{j=i+1}^N A
r^{-12}. \end{equation} Note that \(A\) and \(\rho \) are <span class='cmti-12'>parameters</span>, that need to be somehow determined. This can be done with the help of either experimental data or <span class='cmti-12'>first-principles</span> calculations, that treat the electrons explicitly. These parameters depend on the atom types under consideration and in contrast to the parameter that show up in the Coulomb interaction (the permittivity \(\varepsilon _0\)), they are not universal.</p>
<!--  l. 46  -->
<p class='indent'>For our Na-Cl model, we combine Coulomb interaction with an exponential repulsion, to give the total energy \begin{equation} E_{\text{pot}}(\{\vec{r}_i\}) = \sum _{i=1}^N \sum _{j=i+1}^N \left (A_{ij} e^{-r_{ij}/\rho _{ij}} + \frac{1}{4\pi \varepsilon _0} \frac{q_i q_j}{r_{ij}}\right ). \label{eqn:NaCl} \end{equation} This energy is called the <span class='cmti-12'>potential energy</span> and is the central property of an atomic-scale model. With Eq. \eqref{eqn:NaCl}, we have also
encountered our first atomic-scale model for a real material. Potentials that can be decomposed as Eq. \eqref{eqn:NaCl} into pair-wise terms are called <span class='cmti-12'>pair potentials</span>. They are often written as \begin{equation} E_{\text{pot}}(\{\vec{r}_i\}) = \sum _{i=1}^N \sum _{j=i+1}^N V(r_{ij}), \end{equation} with \begin{equation} V(r_{ij}) = A_{ij} e^{-r_{ij}/\rho _{ij}} + \frac{1}{4\pi \varepsilon _0} \frac{q_i q_j}{r_{ij}} \end{equation} for the above potential. The quantity
\(V(r_{ij})\) is called the pair interaction energy.</p>
<!--  l. 61  -->
<p class='indent'>Likely the most famous pair-potential is the Lennard-Jones potential. Its pair interaction energy is given by \begin{equation} V(r_{ij}) = 4\varepsilon \left [\left (\frac{\sigma }{r}\right )^{12} - \left (\frac{\sigma }{r}\right )^6\right ]. \end{equation} The repulsive term \(\propto r^{-12}\) is one of the models for Pauli repulsion discussed above. The attractive term \(\propto r^{-6}\) arises from <span class='cmti-12'>London dispersion interactions</span>. Dispersion forces exist
between all atoms, even uncharged molecules or noble gases. They are widely employed for the nonbonded portion of valence force-fields. Simple Lennard-Jones systems are often used to study generic phenomena found in real materials, e.g. for example the glass transition or plasticity of amorphous materials. There are limitations of pair potentials and more sophisticated potential energy models have been developed over the past decades. We will discuss a few of those in Chapter <span class='cmbx-12'>??</span>.</p>
<div class='framedenv' id='shaded*-1'><!--  l. 67  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Note:</span></span> A repulsive term of the form \(r^{-12}\) is more attractive from a simulation point of view since it is faster to compute than an exponential. This has helped popularize the Lennard-Jones potential in the early days of molecular dynamics simulations.</p>
</div>
<!--  l. 71  -->
<p class='indent'>The significance of the potential energy is that we can derive forces from it, \begin{equation} \vec{f}_k = -\frac{\partial }{\partial \vec{r}_k} E_{\text{pot}}(\{\vec{r}_i\}). \label{eq:forces} \end{equation} These forces are the essential ingredient to <span class='cmti-12'>molecular dynamics</span>, as they determine the motion of the atoms.</p>
<!--  l. 78  -->
<p class='indent'>The potential energy itself describes what is called the <span class='cmti-12'>potential energy</span> <span class='cmti-12'>landscape</span>. The potential energy landscape depends on \(3N\) degrees of freedom (as compared to the landscape we experience while walking, which depends on \(2\) degrees of freedom); it is therefore an object that is complex to visualize. Simplifying aspects of it is the core of <span class='cmti-12'>molecular statics</span>. For example, it is typically
important to at least identify the ground-state of a system; this is the most stable configuration of a material and has the lowest possible potential energy. There is usually some crystal that is lower in energy than the energy of a glass with the same stoichiometry. Yet, in many real-world engineering applications the materials are not in their crystalline ground-state, the most common material we encounter with this property may be window glass. In molecular statics we therefore seek to enumerate those
<span class='cmti-12'>local</span> <span class='cmti-12'>minima</span> of the potential energy landscape and energy barriers between them.</p>
<!--  l. 80  -->
<p class='indent'>Since the dynamics of a molecular system is determined by the forces, we only need to specify the potential energy up to a constant which disappears in the derivative Eq. \eqref{eq:forces}. We can therefore measure the potential energy with respect to any reference configuration. This reference configuration is often the atomized state of the material, where all of the constituent atoms sit individually in vacuum and are not interacting with each other. If this reference situation is
assigned the energy \(0\), then the potential energy is generally negative, because if it was positive the system would spontaneously atomize. (Remember, any physical system evolves to a state of lower energy.)</p>
