
env = Environment(CPPPATH=['.', 'test'])

main = env.Program('thinner', ['main.cpp', 'thinner.cpp'])
test = env.Program('thinner_test', ['thinner.cpp', Glob('test/*.cpp')])

Default(main, test)
