N = int(input())
data = []
for i in range(N):
    evidence = set(input())
    data.append(evidence)

M = int(input())
max_rank = 0
plates = []
for i in range(M):
    plate = input()
    plate_set = set(plate)
    rank = 0
    for evidence in data:
        if evidence.issubset(plate_set):
            rank += 1
    if rank > max_rank:
        max_rank = rank
    plates.append((plate, rank))

for plate, rank in plates:
    if rank == max_rank:
        print(plate)

