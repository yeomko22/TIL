def solution(skill_tree, skill_trees):
    answer = 0
    skill_list = [c for c in skill_tree]
    skill_dict = {x: i for i, x in enumerate(skill_list)}
    skill_set = set(skill_list)
    for skills in skill_trees:
        flag = True
        prev_index = 0
        cur_skills = [c for c in skills]
        for s in cur_skills:
            if s not in skill_set:
                continue
            cur_index = skill_dict[s]
            if prev_index!=cur_index:
                flag = False
                break
            prev_index += 1
        if flag:
            answer += 1
    return answer
