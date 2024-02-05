REPS = 100
t = 0
for i in range(0, REPS):
    beg = process_time()
    func(...)
    end = process_time()
    t += end - beg
print('Время:', t / REPS)