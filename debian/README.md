# u-boot-olinuxino


## Update the tags

Add the original repository as a new remote:
```sh
git remote add upstream https://github.com/u-boot/u-boot
git fetch upstream
```

Push all tags from ***upstream*** to ***origin***:
```sh
git push origin --tags
```

## Create release

Update the changelog:
```
gbp dch -D unstable -N VERSION --git-author
```

Create tag:
```
gbp buildpackage --git-tag-only
```

Push the tag and the GitLab runner should deploy the package
```
git push origin debian/VERSION
```
