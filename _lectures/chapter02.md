---
layout: default
title: "Chapter 02"
parent: Lectures
date: 2021-04-22
categories: lecture
author: Lars Pastewka
nav_order: 02
---

<h2 class='chapterHead'><span class='titlemark'>Chapter 1</span><br />
<a id='x1-10001'></a>Molecular dynamics</h2>
<div class='framedenv' id='shaded*-1'><!--  l. 3  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Context:</span></span> Molecular <span class='cmti-12'>dynamics</span> follows the motion of individual atoms through a solution of Newton’s equations of motion. We need integration algorithms to be able to solve this set of coupled differential equations on a computer.</p>
</div>
<h3 class='sectionHead'><span class='titlemark'>1.1</span> <a id='x1-20001.1'></a>Newton’s equations of motion</h3>
<!--  l. 14  -->
<p class='noindent'>We have now (almost) all the ingredients to carry out a molecular dynamics simulation. From our or potential energy expression <span class='cmmi-12'>E</span><sub>pot</sub>(<span class='cmsy-10x-x-120'>{</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub><span class='cmsy-10x-x-120'>}</span>) discussed in the previous chapter, we obtain the force</p>
<table class='equation'>
<tr>
<td><a id='x1-2001r1'></a>
<center class='math-display'><img alt='⃗fi = ∂Epot∕∂⃗ri ' src='ch020x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.1)</td>
</tr>
</table>
<!--  l. 17  -->
<p class='nopar'>on each of the <span class='cmmi-12'>N</span> atoms. Once we know the forces, we can obtain the accelerations <span class='accentvec'><span class='cmmi-12'>a</span></span><sub><span class='cmmi-8'>i</span></sub> through Newton’s third law,</p>
<table class='equation'>
<tr>
<td><a id='x1-2002r2'></a>
<center class='math-display'><img alt='⃗fi = mi⃗ai. ' src='ch021x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.2)</td>
</tr>
</table>
<!--  l. 21  -->
<p class='nopar'>We are therefore assuming that atom <span class='cmmi-12'>i</span> can be described as a point of mass <span class='cmmi-12'>m</span><sub><span class='cmmi-8'>i</span></sub>! The mass can be obtained from the periodic table of elements. Note that the mass listed in the periodic table is usually the average over all isotopes weighted by their occurrence on earth, and this mass is used for most practical purposes. For some application, in particular to understand the different behavior of
Hydrogen and Deuterium, it can be necessary to actually model the individual isotopes by using their respective mass.</p>
<!--  l. 24  -->
<p class='indent'>We further have <span class='accentvec'><span class='cmmi-12'>a</span></span><sub><span class='cmmi-8'>i</span></sub> = <span class='accentdot'><span class='accentvec'><span class='cmmi-12'>v</span></span></span><sub><span class='cmmi-8'>i</span></sub>, where <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub> is the velocity of atom <span class='cmmi-12'>i</span>, and <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub> = <span class='accentdot'><span class='accentvec'><span class='cmmi-12'>r</span></span></span><sub><span class='cmmi-8'>i</span></sub>. The dot superscript indicates derivative with respect to time. The set of linear differential equations to solve is therefore</p>
<table class='equation'>
<tr>
<td><a id='x1-2003r3'></a>
<center class='math-display'><img alt='˙v(t) = ⃗f (t)∕m and ˙⃗r (t) = ⃗v (t) i i i i i ' src='ch022x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.3)</td>
</tr>
</table>
<!--  l. 28  -->
<p class='nopar'>with the initial (boundary) conditions <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(0) = <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmr-8'>0</span></sub> and <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(0) = <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmr-8'>0</span></sub>. Note that the boundary condition
is an integral part of the differential Eq. (<a href='#x1-2003r3'>1.3<!--  tex4ht:ref: eq:Newton   --></a>). The state of the system is therefore fully and uniquely determined by the positions <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub> and the velocities <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub> of all atoms. This set of positions <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub> and momenta <span class='accentvec'><span class='cmmi-12'>p</span></span><sub><span class='cmmi-8'>i</span></sub> = <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub><span class='cmmi-12'>∕m</span><sub><span class='cmmi-8'>i</span></sub> defines a point in <span class='cmti-12'>phase-space</span> <span class='accentvec'>Γ</span> = <span class='cmsy-10x-x-120'>{</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub><span class='cmmi-12'>,</span><span class='accentvec'><span class='cmmi-12'>p</span></span><sub><span class='cmmi-8'>i</span></sub><span class='cmsy-10x-x-120'>}</span>. The evolution of position and velocities given by Eq. (<a href='#x1-2003r3'>1.3<!--  tex4ht:ref: eq:Newton   --></a>) can therefore be thought of as a single point moving in the 6<span class='cmmi-12'>N</span> dimensional phase-space. The concept of
a phase-space will become important in the next chapter when we talk about statistical mechanics.</p>
<div class='framedenv' id='shaded*-1'><!--  l. 31  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Code example:</span></span> For a molecular dynamics code, it is useful to have a data structure that represents the state of the simulation and stores at least positions and velocities. This data structure could also store element names (or atomic numbers), masses and forces. An example that uses <a href='https://eigen.tuxfamily.org/'>Eigen</a> arrays as the basic array container is shown below.</p>
<!--  l. 33  -->
<div class='lstlisting' id='listing-1'><span class='label'><a id='x1-2004r1'></a><span class='cmr-6'>1</span></span><span class='cmtt-10'>using Positions_t = Eigen::Array3Xd; </span><br />
<span class='label'><a id='x1-2005r2'></a><span class='cmr-6'>2</span></span><span class='cmtt-10'>using Velocities_t = Eigen::Array3Xd; </span><br />
<span class='label'><a id='x1-2006r3'></a><span class='cmr-6'>3</span></span><span class='cmtt-10'>using Forces_t = Eigen::Array3Xd; </span><br />
<span class='label'><a id='x1-2007r4'></a><span class='cmr-6'>4</span></span><span class='cmtt-10'> </span><br />
<span class='label'><a id='x1-2008r5'></a><span class='cmr-6'>5</span></span><span class='cmtt-10'>class Atoms { </span><br />
<span class='label'><a id='x1-2009r6'></a><span class='cmr-6'>6</span></span><span class='cmtt-10'>public: </span><br />
<span class='label'><a id='x1-2010r7'></a><span class='cmr-6'>7</span></span><span class='cmtt-10'>    Positions_t positions; </span><br />
<span class='label'><a id='x1-2011r8'></a><span class='cmr-6'>8</span></span><span class='cmtt-10'>    Velocities_t velocities; </span><br />
<span class='label'><a id='x1-2012r9'></a><span class='cmr-6'>9</span></span><span class='cmtt-10'>    Forces_t forces; </span><br />
<span class='label'><a id='x1-2013r10'></a><span class='cmr-6'>10</span></span><span class='cmtt-10'> </span><br />
<span class='label'><a id='x1-2014r11'></a><span class='cmr-6'>11</span></span><span class='cmtt-10'>    Atoms(Positions_t &amp;p) : </span><br />
<span class='label'><a id='x1-2015r12'></a><span class='cmr-6'>12</span></span><span class='cmtt-10'>            positions{p}, velocities{3, p.cols()}, forces{3, p.cols()} { </span><br />
<span class='label'><a id='x1-2016r13'></a><span class='cmr-6'>13</span></span><span class='cmtt-10'>        velocities.setZero(); </span><br />
<span class='label'><a id='x1-2017r14'></a><span class='cmr-6'>14</span></span><span class='cmtt-10'>        forces.setZero(); </span><br />
<span class='label'><a id='x1-2018r15'></a><span class='cmr-6'>15</span></span><span class='cmtt-10'>    } </span><br />
<span class='label'><a id='x1-2019r16'></a><span class='cmr-6'>16</span></span><span class='cmtt-10'> </span><br />
<span class='label'><a id='x1-2020r17'></a><span class='cmr-6'>17</span></span><span class='cmtt-10'>    size_t nb_atoms() { </span><br />
<span class='label'><a id='x1-2021r18'></a><span class='cmr-6'>18</span></span><span class='cmtt-10'>        return positions.cols(); </span><br />
<span class='label'><a id='x1-2022r19'></a><span class='cmr-6'>19</span></span><span class='cmtt-10'>    } </span><br />
<span class='label'><a id='x1-2023r20'></a><span class='cmr-6'>20</span></span><span class='cmtt-10'>};</span></div>
<!--  l. 55  -->
<p class='indent'>As a general rule, the data structure should be designed in a way that data that is processed consecutively is also stored in memory in a continuous manner. This ensures <a href='https://en.wikipedia.org/wiki/Cache_coherence'>cache coherenece</a>. For example, we could be tempted to create a class <span class='obeylines-h'><span class='verb'><span class='cmtt-12'>Atom</span></span></span> that contains the positions, velocities, etc. of a single atom and than use an array (e.g.
<span class='obeylines-h'><span class='verb'><span class='cmtt-12'>std::vector&lt;Atom&gt; atoms</span></span></span>) of that class as the basic data structure. However, positions are then no longer consecutive in memory. A function (e.g. computing forces) does not need the velocities would still load them into the cache, as the <a href='https://en.wikipedia.org/wiki/CPU_cache'>cache line size</a> for all modern CPUs is 64 bytes. For high-performance numerical code, it is therefore <span class='cmti-12'>always</span> preferable to use structures of arrays rather than arrays of structure.</p>
</div>
<!--  l. 58  -->
<p class='noindent'></p>
<h3 class='sectionHead'><span class='titlemark'>1.2</span> <a id='x1-30001.2'></a>Kinetic energy and energy conservation</h3>
<!--  l. 60  -->
<p class='noindent'>In addition to the potential energy <span class='cmmi-12'>E</span><sub>pot</sub>(<span class='cmsy-10x-x-120'>{</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub><span class='cmsy-10x-x-120'>}</span>), the dynamical state of a system is characterized by its kinetic energy,</p>
<table class='equation'>
<tr>
<td><a id='x1-3001r4'></a>
<center class='math-display'><img alt=' ∑ 2 Ekin({⃗pi}) = 1-pi. i 2mi ' src='ch023x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.4)</td>
</tr>
</table>
<!--  l. 63  -->
<p class='nopar'>Note that the total energy</p>
<table class='equation'>
<tr>
<td><a id='x1-3002r5'></a>
<center class='math-display'><img alt='H ({⃗ri},{⃗pi}) = Ekin({⃗pi} ) + Epot({⃗ri}) ' src='ch024x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.5)</td>
</tr>
</table>
<!--  l. 68  -->
<p class='nopar'>is a conserved quantity during the motion of the atoms. This can be seen by showing that the derivative of the total energy with respect to time vanishes,</p>
<table class='equation'>
<tr>
<td><a id='x1-3003r6'></a>
<center class='math-display'><img alt=' ∑ ˙ ∑ ∑ ∑ H˙ = E˙kin + E˙pot = ⃗pi⃗pi+ ∂Epot⃗r˙i = ⃗vif⃗i − ⃗vif⃗i = 0. i mi i ∂⃗ri i i ' src='ch025x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.6)</td>
</tr>
</table>
<!--  l. 73  -->
<p class='nopar'><span class='cmmi-12'>H</span> is also called the <span class='cmti-12'>Hamiltonian</span> of the system.</p>
<div class='framedenv' id='shaded*-1'><!--  l. 76  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Note:</span></span> Measuring the total energy (or any other conserved quantity!) and checking whether it is constant in a molecular dynamics simulation is a way of testing if the time step Δ<span class='cmmi-12'>t</span> used in the numerical integration is small enough. We will discuss numerical integration in detail below.</p>
</div>
<!--  l. 80  -->
<p class='indent'>A generalization of Newton’s equations of motion are <span class='cmti-12'>Hamilton’s equation of</span> <span class='cmti-12'>motion</span>,</p>
<table class='align'>
<tr>
<td class='align-odd'><span class='accentdot'><span class='accentvec'><span class='cmmi-12'>r</span></span></span><sub><span class='cmmi-8'>i</span></sub></td>
<td class='align-even'>= <img class='frac' src='ch026x.svg' align='middle' alt='∂H ---- ∂⃗pi' /></td>
<td class='align-label'><a id='x1-3004r7'></a>(1.7)</td>
</tr>
<tr>
<td class='align-odd'><span class='accentdot'><span class='accentvec'><span class='cmmi-12'>p</span></span></span><sub><span class='cmmi-8'>i</span></sub></td>
<td class='align-even'>= <span class='cmsy-10x-x-120'>−</span><img class='frac' src='ch027x.svg' align='middle' alt='∂H-- ∂⃗ri' /><span class='cmmi-12'>,</span></td>
<td class='align-label'><a id='x1-3005r8'></a>(1.8)</td>
</tr>
</table>
<!--  l. 85  -->
<p class='indent'>and it is straightforward to show that this reduces to Newton’s equations of motions for the Hamiltonian given by Eq. (<a href='#x1-3002r5'>1.5<!--  tex4ht:ref: eq:hamil   --></a>). Hamilton’s equation of motion remain valid when positions <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub> and momenta <span class='accentvec'><span class='cmmi-12'>p</span></span><sub><span class='cmmi-8'>i</span></sub> are replaced by generalized
coordinates that consider constraints, such as for example the angle of a (rigid) pendulum. These equations will become important when we discuss statistical mechanics and temperature control in molecular dynamics simulations using <span class='cmti-12'>thermostats</span>, where a generalized degree of freedom is the internal state of the heat bath that controls the temperature. A full derivation of Hamilton’s equations of motion is given in Chap. <span class='cmbx-12'>??</span>.</p>
<div class='framedenv' id='shaded*-1'><!--  l. 87  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Note:</span></span> The <span class='cmti-12'>temperature</span> is simply a measure of the kinetic energy of the system, <img class='frac' src='ch028x.svg' align='middle' alt='32' /><span class='cmmi-12'>Nk</span><sub><span class='cmmi-8'>B</span></sub><span class='cmmi-12'>T</span> = <span class='cmmi-12'>E</span><sub>kin</sub> where <span class='cmmi-12'>N</span> is the number of atoms. In other words, <span class='cmmi-12'>E</span><sub>kin</sub> measures the variance of the velocity distribution, which is Gaussian. We will learn more about this when discussing the basics of statistical mechanics.</p>
</div>
<!--  l. 91  -->
<p class='noindent'></p>
<h3 class='sectionHead'><span class='titlemark'>1.3</span> <a id='x1-40001.3'></a>Integration algorithms</h3>
<!--  l. 94  -->
<p class='noindent'>The main ingredient in any molecular dynamics simulation, regardless of the underlying model, is the numerical solution of Eqs. (<a href='#x1-2003r3'>1.3<!--  tex4ht:ref: eq:Newton   --></a>). A plethora of algorithms have been developed over the years, but for most practical purposes the Velocity-Verlet algorithm is used nowadays. For instructive purposes we will start out with a simple integration method, the Euler integration, before discussing Velocity-Verlet.</p>
<!--  l. 96  -->
<p class='noindent'></p>
<h4 class='subsectionHead'><span class='titlemark'>1.3.1</span> <a id='x1-50001.3.1'></a>Euler integration</h4>
<!--  l. 97  -->
<p class='noindent'>In order to follow the trajectories of all atoms we need to integrate the above differential equation. On a computer, a continuous differential equation needs to be replaced by a discrete equation. Equations (<a href='#x1-2003r3'>1.3<!--  tex4ht:ref: eq:Newton   --></a>) are continuous in time and hence need to be discretized. (Note that our system is already discrete spatially since we are dealing with mass points, but each of these points corresponds to a physical object so this is
not the result of a discretization procedure.) The simplest integration is the Euler algorithm in which forces and velocities are assumed to be constant over time intervals Δ<span class='cmmi-12'>t</span>.</p>
<!--  l. 100  -->
<p class='indent'>To see this, we write the above differential equation as</p>
<table class='equation'>
<tr>
<td><a id='x1-5001r9'></a>
<center class='math-display'><img alt=' ⃗fi(t) d ⃗vi = ----- and d⃗ri(t) = ⃗vi(t)dt mi ' src='ch029x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.9)</td>
</tr>
</table>
<!--  l. 103  -->
<p class='nopar'>i.e., we move the differential <span class='cmmi-12'>dt</span> of <span class='accentdot'><span class='accentvec'><span class='cmmi-12'>v</span></span></span><sub><span class='cmmi-8'>i</span></sub> = <span class='cmmi-12'>d</span><span class='accentvec'><span class='cmmi-12'>v</span></span><span class='cmmi-12'>∕dt</span> to the right hand side of the equation. We can now straightforwardly integrate the equation from time <span class='cmmi-12'>t</span> to time <span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span> while assuming that <span class='accentvec'><span class='cmmi-12'>f</span></span><sub><span class='cmmi-8'>i</span></sub> and <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub> remain constant. This yields</p>
<table class='align'>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>) <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)</td>
<td class='align-even'>= <img class='frac' src='ch0210x.svg' align='middle' alt='f⃗i(t) m i' />Δ<span class='cmmi-12'>t</span></td>
<td class='align-label'><a id='x1-5002r10'></a>(1.10)</td>
</tr>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>) <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)</td>
<td class='align-even'>= <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)Δ<span class='cmmi-12'>t</span></td>
<td class='align-label'><a id='x1-5003r11'></a>(1.11)</td>
</tr>
</table>
<!--  l. 109  -->
<p class='indent'>which is obviously only a good approximation for small Δ<span class='cmmi-12'>t</span>! This algorithm is called Euler integration.</p>
<!--  l. 111  -->
<p class='indent'>Same equation can be derived by Taylor-expanding <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>) up to first order in Δ<span class='cmmi-12'>t</span>. The algorithm is hence <span class='cmmi-12'>O</span>(Δ<span class='cmmi-12'>t</span><sup><span class='cmr-8'>2</span></sup>). The Euler algorithm is not reversible, i.e. starting from time <span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span> and integrating backwards one ends up with a different result at time <span class='cmmi-12'>t</span>. Applying the Euler algorithm with timestep <span class='cmsy-10x-x-120'>−</span>Δ<span class='cmmi-12'>t</span> gives</p>
<table class='align'>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>) <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>)</td>
<td class='align-even'>= <span class='cmsy-10x-x-120'>−</span><img class='frac' src='ch0211x.svg' align='middle' alt='⃗ fi(t +-Δt-) mi' />Δ<span class='cmmi-12'>t</span></td>
<td class='align-label'><a id='x1-5004r12'></a>(1.12)</td>
</tr>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>) <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>)</td>
<td class='align-even'>= <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>)Δ<span class='cmmi-12'>t</span></td>
<td class='align-label'><a id='x1-5005r13'></a>(1.13)</td>
</tr>
</table>
<!--  l. 119  -->
<p class='indent'>These equations cannot be re-arranged to give Eqs. (<a href='#x1-5002r10'>1.10<!--  tex4ht:ref: eq:eulerexplicita   --></a>) and (<a href='#x1-5003r11'>1.11<!--  tex4ht:ref: eq:eulerexplicitb   --></a>). Euler integration is generally not a good algorithm and requires very small time steps.</p>
<!--  l. 124  -->
<p class='noindent'></p>
<h4 class='subsectionHead'><span class='titlemark'>1.3.2</span> <a id='x1-60001.3.2'></a>Leap-frog integration</h4>
<!--  l. 125  -->
<p class='noindent'>Leap-frog stores position at times <span class='cmmi-12'>t</span><sub><span class='cmmi-8'>i</span></sub> and velocities at times <span class='cmmi-12'>t</span><sub><span class='cmmi-8'>i</span></sub> + Δ<span class='cmmi-12'>t∕</span>2 and can be derived from a argument similar to the one given above. Specifically, we combine the results of a Taylor expansion <span class='cmsy-10x-x-120'>±</span>Δ<span class='cmmi-12'>t∕</span>2, yielding</p>
<table class='align'>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t∕</span>2) <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> <span class='cmsy-10x-x-120'>−</span> Δ<span class='cmmi-12'>t∕</span>2)</td>
<td class='align-even'>= <img class='frac' src='ch0212x.svg' align='middle' alt='⃗fi(t) ----- mi' />Δ<span class='cmmi-12'>t</span></td>
<td class='align-label'><a id='x1-6001r14'></a>(1.14)</td>
</tr>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>) <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)</td>
<td class='align-even'>= <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t∕</span>2)Δ<span class='cmmi-12'>t.</span></td>
<td class='align-label'><a id='x1-6002r15'></a>(1.15)</td>
</tr>
</table>
<!--  l. 132  -->
<p class='indent'>Note that Eq. (<a href='#x1-6001r14'>1.14<!--  tex4ht:ref: eq:leapfrog1   --></a>) is similar to Eq. (<a href='#x1-5002r10'>1.10<!--  tex4ht:ref: eq:eulerexplicita   --></a>), except the force is evaluated at the mid-point. The resulting algorithm is reversible. Applying the Leap-frog algorithm with timestep <span class='cmsy-10x-x-120'>−</span>Δ<span class='cmmi-12'>t</span> gives</p>
<table class='align'>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> <span class='cmsy-10x-x-120'>−</span> Δ<span class='cmmi-12'>t∕</span>2) <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t∕</span>2)</td>
<td class='align-even'>= <span class='cmsy-10x-x-120'>−</span><img class='frac' src='ch0213x.svg' align='middle' alt='f⃗i(t) m i' />Δ<span class='cmmi-12'>t</span></td>
<td class='align-label'><a id='x1-6003r16'></a>(1.16)</td>
</tr>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>) <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>)</td>
<td class='align-even'>= <span class='cmsy-10x-x-120'>−</span><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t∕</span>2)Δ<span class='cmmi-12'>t</span></td>
<td class='align-label'><a id='x1-6004r17'></a>(1.17)</td>
</tr>
</table>
<!--  l. 138  -->
<p class='indent'>Bring the terms on the left hand side to the right and vice-versa, and you arrive at the original equations for forward integration. Leap-frog is therefore <span class='cmti-12'>reversible</span>.</p>
<!--  l. 140  -->
<p class='noindent'></p>
<h4 class='subsectionHead'><span class='titlemark'>1.3.3</span> <a id='x1-70001.3.3'></a>Verlet integration</h4>
<!--  l. 142  -->
<p class='noindent'>Let us now Taylor expand <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> <span class='cmsy-10x-x-120'>±</span> Δ<span class='cmmi-12'>t</span>) up to third order in <span class='cmsy-10x-x-120'>±</span>Δ<span class='cmmi-12'>t</span>,</p>
<table class='equation'>
<tr>
<td><a id='x1-7001r18'></a>
<center class='math-display'><img alt=' ˙ ⃗ri(t ± Δt ) = ⃗ri(t) ± ⃗vi(t)Δt + -1--⃗fi(t)Δt2 ± 1-˙˙⃗ri(t)Δt3 + O (Δt4 ). 2mi 6 ' src='ch0214x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.18)</td>
</tr>
</table>
<!--  l. 146  -->
<p class='nopar'>Note that only the odd exponents see the sign of <span class='cmsy-10x-x-120'>±</span>Δ<span class='cmmi-12'>t</span>. The sum of this equation for expansion in +Δ<span class='cmmi-12'>t</span> and <span class='cmsy-10x-x-120'>−</span>Δ<span class='cmmi-12'>t</span> gives the positions update,</p>
<table class='equation'>
<tr>
<td><a id='x1-7002r19'></a>
<center class='math-display'><img alt=' -1-⃗ 2 4 ⃗ri(t + Δt) + ⃗ri(t − Δt ) = 2⃗ri(t) + mi fi(t)Δt + O(Δt ). ' src='ch0215x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.19)</td>
</tr>
</table>
<!--  l. 152  -->
<p class='nopar'>Eq. (<a href='#x1-7002r19'>1.19<!--  tex4ht:ref: eqn: verlet   --></a>) is called the Verlet algorithm. Instead of requiring the positions <span class='cmsy-10x-x-120'>{</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)<span class='cmsy-10x-x-120'>}</span> and velocities <span class='cmsy-10x-x-120'>{</span><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)<span class='cmsy-10x-x-120'>}</span> it requires the positions of the current <span class='cmsy-10x-x-120'>{</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)<span class='cmsy-10x-x-120'>}</span> and past <span class='cmsy-10x-x-120'>{</span><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> <span class='cmsy-10x-x-120'>−</span> Δ<span class='cmmi-12'>t</span>)<span class='cmsy-10x-x-120'>}</span> times for the integration.</p>
<!--  l. 155  -->
<p class='indent'>The difference between the expansion for +Δ<span class='cmmi-12'>t</span> and <span class='cmsy-10x-x-120'>−</span>Δ<span class='cmmi-12'>t</span> yields the velocities,</p>
<table class='equation'>
<tr>
<td><a id='x1-7003r20'></a>
<center class='math-display'><img alt='⃗ri(t + Δt ) − ⃗ri(t − Δt) = 2⃗vi(t)Δt + O (Δt3). ' src='ch0216x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.20)</td>
</tr>
</table>
<!--  l. 158  -->
<p class='nopar'>Note that in order to compute the velocities at time t in the regular Verlet algorithm, we need to know the positions at time <span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>. Verlet and Leap-Frog are identical algorithms, since Leap-Frog stores the velocities at the intermediate time <span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t∕</span>2. It is usually useful to be able to know both, positions and velocities, at time <span class='cmmi-12'>t</span>. This problem
is solved by the Velocity-Verlet algorithm, described in the following section.</p>
<!--  l. 162  -->
<p class='noindent'></p>
<h4 class='subsectionHead'><span class='titlemark'>1.3.4</span> <a id='x1-80001.3.4'></a>Velocity-Verlet integration</h4>
<!--  l. 164  -->
<p class='noindent'>Let us now also Taylor expand <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>) up to third order in Δ<span class='cmmi-12'>t</span> at <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>), i.e. we integrate backwards in time from <span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span> to <span class='cmmi-12'>t</span>. This gives</p>
<table class='equation'>
<tr>
<td><a id='x1-8001r21'></a>
<center class='math-display'><img alt=' 1 1 ˙ ⃗ri(t) = ⃗ri(t + Δt ) − ⃗vi(t + Δt)Δt +----⃗fi(t + Δt )Δt2 − -⃗˙˙ri(t)Δt3 + O (Δt3) 2mi 6 ' src='ch0217x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.21)</td>
</tr>
</table>
<!--  l. 168  -->
<p class='nopar'>Equation (<a href='#x1-7001r18'>1.18<!--  tex4ht:ref: eqn: taylor_tplus   --></a>) is the positions update of the Velocity-Verlet algorithm. The sum of Eq. (<a href='#x1-7001r18'>1.18<!--  tex4ht:ref: eqn: taylor_tplus   --></a>) and Eq. (<a href='#x1-8001r21'>1.21<!--  tex4ht:ref: eqn: taylor_r   --></a>) gives the velocity update in the Velocity-Verlet algorithm:</p>
<table class='align'>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>)</td>
<td class='align-even'>= <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>) + <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)Δ<span class='cmmi-12'>t</span> + <img class='frac' src='ch0218x.svg' align='middle' alt=' 1 ---- 2mi' /><span class='accentvec'><span class='cmmi-12'>f</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)Δ<span class='cmmi-12'>t</span><sup><span class='cmr-8'>2</span></sup></td>
<td class='align-label'><a id='x1-8002r22'></a>(1.22)</td>
</tr>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>)</td>
<td class='align-even'>= <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>) + <img class='frac' src='ch0219x.svg' align='middle' alt='-1-- 2mi' /><img class='left' src='ch0220x.svg' align='middle' alt='( ) ⃗f (t) + ⃗f (t + Δt ) i i' /> Δ<span class='cmmi-12'>t,</span></td>
<td class='align-label'><a id='x1-8003r23'></a>(1.23)</td>
</tr>
</table>
<!--  l. 174  -->
<p class='indent'>Note that this algorithm is often split in the form of a predictor-corrector scheme since this saves computation time and the necessity to keep past forces around. The predictor step is</p>
<table class='align'>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t∕</span>2)</td>
<td class='align-even'>= <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>) + <img class='frac' src='ch0221x.svg' align='middle' alt='--1- 2mi' /><span class='accentvec'><span class='cmmi-12'>f</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>)Δ<span class='cmmi-12'>t</span></td>
<td class='align-label'><a id='x1-8004r24'></a>(1.24)</td>
</tr>
<tr>
<td class='align-odd'><span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>)</td>
<td class='align-even'>= <span class='accentvec'><span class='cmmi-12'>r</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span>) + <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t∕</span>2)Δ<span class='cmmi-12'>t</span></td>
<td class='align-label'><a id='x1-8005r25'></a>(1.25)</td>
</tr>
</table>
<!--  l. 182  -->
<p class='indent'>where <span class='accentvec'><span class='cmmi-12'>v</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t∕</span>2) is the predicted velocity. After this we compute new forces, <span class='accentvec'><span class='cmmi-12'>f</span></span><sub><span class='cmmi-8'>i</span></sub>(<span class='cmmi-12'>t</span> + Δ<span class='cmmi-12'>t</span>). We then correct the velocities via</p>
<table class='equation'>
<tr>
<td><a id='x1-8006r26'></a>
<center class='math-display'><img alt='⃗v (t + Δt ) = ⃗v(t + Δt ∕2) +-1--⃗f(t + Δt)Δt i i 2mi i ' src='ch0222x.svg' class='math-display' /></center>
</td>
<td class='equation-label'>(1.26)</td>
</tr>
</table>
<!--  l. 186  -->
<p class='nopar'>The Velocity-Verlet algorithm is the integration algorithm used in most molecular dynamics codes. It has the additional properties that is it <span class='cmti-12'>symplectic</span>, which means it conserves phase-space volume. We will come back to what this mean when talking about statistical mechanics.</p>
<div class='framedenv' id='shaded*-1'><!--  l. 189  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Code example:</span></span> We can implement the velocity-verlet algorithm in a few lines of C++ code using vectorized <span class='obeylines-h'><span class='verb'><span class='cmtt-12'>Eigen</span></span></span> operations. The prediction step</p>
<!--  l. 191  -->
<div class='lstlisting' id='listing-2'><span class='label'><a id='x1-8007r1'></a><span class='cmr-6'>1</span></span><span class='cmtt-10'>void verlet_step1(Atoms &amp;atoms, double timestep, double mass) { </span><br />
<span class='label'><a id='x1-8008r2'></a><span class='cmr-6'>2</span></span><span class='cmtt-10'>    atoms.velocities += 0.5 * atoms.forces * timestep / mass; </span><br />
<span class='label'><a id='x1-8009r3'></a><span class='cmr-6'>3</span></span><span class='cmtt-10'>    atoms.positions += atoms.velocities * timestep; </span><br />
<span class='label'><a id='x1-8010r4'></a><span class='cmr-6'>4</span></span><span class='cmtt-10'>}</span></div>
<!--  l. 197  -->
<p class='indent'>implements Eq. (<a href='#x1-8004r24'>1.24<!--  tex4ht:ref: eq:vvpred1   --></a>). We then compute new forces and correct the velocities via</p>
<!--  l. 198  -->
<div class='lstlisting' id='listing-3'><span class='label'><a id='x1-8011r1'></a><span class='cmr-6'>1</span></span><span class='cmtt-10'>void verlet_step2(Atoms &amp;atoms, double timestep, double mass) { </span><br />
<span class='label'><a id='x1-8012r2'></a><span class='cmr-6'>2</span></span><span class='cmtt-10'>    atoms.velocities += 0.5 * atoms.forces * timestep / mass; </span><br />
<span class='label'><a id='x1-8013r3'></a><span class='cmr-6'>3</span></span><span class='cmtt-10'>}</span></div>
</div>
<div class='framedenv' id='shaded*-1'><!--  l. 208  -->
<p class='noindent'><span class='underline'><span class='cmbx-12'>Note:</span></span> The timestep in MD simulations has to be on the order of femtoseconds, in order to resolve the fastest atomic vibrations. For example, in simulations with metals and Embedded Atom Method (EAM) potentials, Δ<span class='cmmi-12'>t</span> = 1 fs is typically a safe choice. How can we check that the timestep is sensible? One possibility is to simply propage a configuration in time using the Velocity-Verlet algorithm.
This is sometimes called the micro-canonical or NVE ensemble. (NVE because number of atoms, volume and energy is constant.) We then record the evolution of the total (kinetic plus potential) energy, which should be constant. The discrete time integration scheme will introduce numerical errors. If Δ<span class='cmmi-12'>t</span> is too large, there will be noticeable drift of the total energy. The figures below show the results of such a simulation. A system of 108000 Au atoms was simulated for 100 ps
with various values of Δ<span class='cmmi-12'>t</span>. The <span class='cmmi-12'>y</span>-axis shows the difference between the current and initial values of the total energy. The data was smoothened to suppress high-frequency fluctuations in the figure. For this system, even 5 fs would still be an acceptable time step.</p>
<div class='center'><!--  l. 219  -->
<p class='noindent'></p>
<!--  l. 220  -->
<p class='noindent'><img alt='PIC' height='390' src='figures/etot_vs_time_as_function_of_timestep_Grochola_Au_NVE_ensemble_01.png' width='390' /> <img alt='PIC' height='390' src='figures/etot_vs_time_as_function_of_timestep_Grochola_Au_NVE_ensemble_02.png' width='390' /></p>
</div>
</div>
