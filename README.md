# Molecular Dynamics with C++

This repository contains the source code for the class "High-Performance Computing: Molecular Dynamic with C++" at the University of Freiburg. The compiled pages can be accessed [here](https://imtek-simulation.github.io/MolecularDynamics/).

## Local development

To host the site locally, create a file `_config.docker.yml` with the following contents:
```yaml
url: "http://localhost:4000"
```

Then run:
```bash
JEKYLL_VERSION=4.0 docker run --rm -e "JEKYLL_ENV=docker" --name MDLecture --volume="$PWD:/srv/jekyll" -p 4000:4000 -it jekyll/jekyll jekyll serve --config _config.yml,_config.docker.yml
```

The site can be restarted with
```bash
docker restart MD
```

## Updating Jekyll

To update the Jekyllversion run:
```bash
JEKYLL_VERSION=4.0 docker run --rm -e "JEKYLL_ENV=docker" --name MDLecture --volume="$PWD:/srv/jekyll" -p 4000:4000 -it jekyll/jekyll bundle update github-pages
```