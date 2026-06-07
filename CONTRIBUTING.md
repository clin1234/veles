# Contributing to Veles
## Reporting bugs
If you find a bug in Veles please check first if the problem has been already
reported. Gather following information:
* Steps how to reproduce the problem.
* Veles version (Help/about)
* Operating system version:
  * Linux - output of `uname -a` and `cat /etc/os-release`.
  * MacOSX - output of `uname -a` and `sw_vers -productVersion`.
  * Windows - use this [guide][ms_guide].
* If running on Linux or MacOSX - output of `glxinfo | grep string`.

and create an issue on GitHub.

## Submitting changes
 
### Style
We are trying to stick as close as possible to [Google C++ Style Guide].
Refer to this document whenever in doubt.
However:
* We use `#pragma once`.
* We have to use raw pointers in many places, because of Qt.
* We don't like the Hungarian notation used for constants, so maybe we will
  switch to CAPS_NOTATION at some point.

Notice you might find some older code that doesn't conform to GCS.

### Contribution pipeline

* Create your own branch. Name it `wip/your_GitHub_nick/descriptive-branch-name`.
* Develop your branch. Remember to:
  * Keep your commits atomic (one feature per commit).
  * Add descriptive commit messages. One-liners are fine for small,
    obvious changes, but bigger changes should have longer commit messages.
  * Make sure the email in your commits metadata is linked with your GitHub
    account.
  * Use `format` build target (for Linux run `make format`) relatively
    often to avoid huge "Style fix" commits.
* When you think you're done open a GitHub PR with a clear list of what you
  did. From now on your branch is *public* and you shouldn't forcepush
  (`git push -f`) anything to it. If you really need to/want to pushforce
  *first* ask reviewers for permission.
* Every PR has to pass clang-tidy checks (`lint` build target).
* Submit fixes according to the review in new commits.
* Once your code is accepted by reviewers, please squash your fixes
  into previous feature commits.
* Your code will be merged into master.

### File placement
We have some rules as to where to place new files:
* All things that depend on Qt should be placed in `ui` folder
* There should be as few things in `util` folder as possible. `util` is only
  for pieces of code that don't belong to any existing folders and are too small
  to have their own folder
* Place C++ source files generated from `kaitai-struct-compier` in `src\kaitai`,
and C++ headers generated from `kaitai-struct-compier` in `include\kaitai`

### Special Kaitai Struct Instructions

Right now, Veles relies on a
[heavily-tweaked fork of the Kaitai Struct Compiler](https://github.com/codilime/kaitai_struct_compiler/tree/hacks/veles),
which is based off of either 0.5 or 0.6 of the compiler.
As such, this repo only contains .ksy files that either don't contain ks-version or has ks-version no newer than 0.6:
https://github.com/clin1234/kaitai_struct_formats/tree/veles_compatible.
You can download a build of this fork of the compiler here:
https://github.com/clin1234/kaitai_struct_compiler/actions/workflows/main.yml?query=is%3Asuccess

When adding a new format, source and header files generated from the compiler must be further modified:

* Header (.h): declare `veles::dbif::ObjectHandle veles_obj` as a public member in each class and subclass
* Source file (.cc): within each constructor, do the following:
  - Surround each assignment of any member prefixed with `m_` (excluding `m__io`) with `m__io->pushName("<member name>");`
  and `m__io->popName();`
  - Include `veles_obj = m__io->startChunk("<class name>");` before any call to `new kaitai::kstream` and `m__io->endChunk();`
  as the last function call within the constructor definition

After massaging these files, create an `include\kaitai\<formatname>_parser.h` with the following format:
```c++
#include "kaitai/formatname.h"
#include "parser/parser.h"

namespace veles {
namespace kaitai {

class formatnameParser : public parser::Parser {
 public:
  formatnameParser() : parser::Parser("formatname (ksy)") {}
  void parse(const dbif::ObjectHandle& blob, uint64_t start,
             const dbif::ObjectHandle& parent_chunk) override {
    try {
      auto stream = kaitai::kstream(blob, start, parent_chunk);
      auto parser = formatname_t(&stream);
    } catch (const std::exception&) {
    }
  }
};

}  // namespace kaitai
}  // namespace veles
``` 

And construct the parser in `createAllParsers()` at `src\parser\utils.cc`:
```c++
QList<Parser*> createAllParsers() {
  QList<Parser*> res;
  ...
  res.append(new kaitai::formatnameParser());
  return res;
}
```

Thanks for taking the time to contribute to Veles!

[Google C++ Style Guide]: <https://google.github.io/styleguide/cppguide.html>
[ms_guide]: <https://support.microsoft.com/en-us/help/13443/windows-which-operating-system>
