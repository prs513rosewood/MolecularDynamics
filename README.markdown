# Molecular Dynamics with C++

This repository contains the source code for the class "High-Performance Computing: Molecular Dynamic with C++" at the University of Freiburg. The compiled pages can be accessed [here](https://imtek-simulation.github.io/MolecularDynamics/).

## Local development

To host the site locally, run

```bash
JEKYLL_VERSION=4.0 docker run --name MD --volume="$PWD:/srv/jekyll" -p 4000:4000 -it jekyll/jekyll:$JEKYLL_VERSION jekyll serve
```

The site can be restarted with
```bash
docker restart MD
```