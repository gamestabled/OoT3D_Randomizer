#!/bin/bash

# This script creates the name for the release git tag and the version string to show in the randomizer menu.
# It generates a header file with a macro for the version string.

VERSION_FILE="source/version.hpp"

if [[ -n $GITHUB_ENV ]]
then
    # Building from GitHub Actions
    # GITHUB_BUILD_TYPE and GITHUB_INPUT_VERSION are defined in `create_build.yml`

    if [[ "$GITHUB_BUILD_TYPE" = "Release" ]]
    then
        VERSION="v$GITHUB_INPUT_VERSION"
    else
        VERSION="$GITHUB_BUILD_TYPE-${GITHUB_SHA::6}"
    fi
    echo "tag_name=$VERSION" >> $GITHUB_ENV
else
    # Building locally
    VERSION=dev-$(git show --no-patch --format=format:"%h" --abbrev=6)

    # If there are uncommitted changes, add a `*` to the version.
    if [[ -n $(git status --porcelain) ]]
    then
        VERSION="${VERSION}*"
    fi
fi

# If the version string doesn't change, don't rewrite the file to avoid useless rebuilds.
NEW_CONTENT="#define RANDOMIZER_VERSION \"$VERSION\""
OLD_CONTENT="$(cat "$VERSION_FILE" 2> /dev/null || true)"
if [[ "$NEW_CONTENT" != "$OLD_CONTENT" ]]
then
    echo "$NEW_CONTENT" > "$VERSION_FILE"
    echo "Wrote version string: $VERSION"
fi
