# Security Policy

## Supported Versions

This project was built as a university course assignment (Fundamentals of Programming) and is now complete — it's not under active development. I'll still do my best to review and fix genuine security reports on `main`, but response times may be slow since this isn't a maintained product.

| Version               | Supported                    |
| ---------------------- | ----------------------------- |
| `main` (latest commit) | :white_check_mark: (best effort) |
| Older tags/releases    | :x:                            |

## Scope

`othello-v1.c` is a standalone, offline C program:
- No network access
- No external dependencies
- No storage of user data (scores/names exist only in memory during play)

Because of this, the attack surface is intentionally small. Still, reports are welcome for things like:
- Buffer overflows / out-of-bounds writes (e.g. around `scanf` usage or the board arrays)
- Crashes caused by malformed or oversized input
- Any undefined behavior found via tools like `valgrind`, ASan/UBSan, or static analyzers

## Reporting a Vulnerability

Please **do not** open a public issue for security-sensitive bugs.

Instead:
1. Open a [GitHub Security Advisory](../../security/advisories/new) for this repo, **or**
2. Contact the maintainer directly via the email listed on the [GitHub profile](https://github.com/amirmohammadshir1386-web)

When reporting, please include:
- A clear description of the issue
- Steps to reproduce (sample input, compiler/OS used)
- The potential impact

I'll do my best to review reports and respond within a few days, and will credit reporters in the README/changelog once a fix is merged (if you'd like).
