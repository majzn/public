def Settings( **kwargs ):
  return {
    'flags': [ '-x', 'c', '-std=c99' 'pedantic', 'ansi' , '-Wall', '-Wpadded', '-Wextra', '-Wno-unused-functions', '-Wno-unused-parameter', '-Werror', '-Wwrite-strings', '-Wstrict-prototypes', '-Wfloat-equal', '-Wdeclaration-after-statement', '-Wbad-function-cast', '-Wpointer-arith', '-Wredundant-decls', '-Wunreachable-code', '-Wundef', '-Wswitch', '-Wshadow', '-Wsequence-point'],
  }
