Inform 6 Language Grammar for Atom

- Created by Jeff Nyman <jeffnyman@gmail.com>
- https://github.com/jeffnyman/language-inform6
- https://atom.io/packages/language-inform6

This package permits syntax coloring of [Inform 6][i6] source code in the [Atom][] editor. This should also work with compatible syntax colorers, like TextMate 2, with some appropriate changes for the particulars of how grammar files are specified.

Note that this package does not deal with [Inform 7][i7]. Andrew Plotkin has already written an [Inform 7 language file][i7lang].

[i6]: https://github.com/DavidKinder/Inform6
[i7]: http://inform7.com/
[i7lang]: https://github.com/erkyrath/language-inform7
[atom]: https://atom.io/

This language extension correctly handles:

- Comments
- Strings (double and single)
- Directives
- Keywords
- Function definitions

Note that Inform 6 uses two file extensions, `inf` and `h`, that are very commonly used by multiple other languages.

If you want to customize what language package is used when loading a file of a certain extension, Atom can be configured to do this. You'll need to manually edit your Atom `config.cson` file and add this if you want Inform 6 to be the default:

    "*":
      core:
        customFileTypes:
          "source.inform6": [
            "inf"
            "h"
          ]