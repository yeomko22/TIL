"""
recursion limit을 설정해주지 않으면 런타임 에러가 뜬다.
"""
from sys import setrecursionlimit

class Node:
    def __init__(self, num, x, parent=None):
        self.num = num
        self.x = x
        self.parent = parent
        self.left = None
        self.right = None

    def __str__(self):
        return f'value:{self.num}, x:{self.x}'


def forward_traversal(node, answer):
    answer.append(node.num)
    if node.left:
        forward_traversal(node.left, answer)
    if node.right:
        forward_traversal(node.right, answer)
    return answer


def backward_traversal(node, answer):
    if node.left:
        backward_traversal(node.left, answer)
    if node.right:
        backward_traversal(node.right, answer)
    answer.append(node.num)
    return answer


def solution(nodeinfo):
    setrecursionlimit(10000000)
    answer = [[]]
    nodeinfo = [(i+1, (x[0], x[1])) for i, x in enumerate(nodeinfo)]
    sorted_nodes = sorted(nodeinfo, key=lambda x:x[1][1], reverse=True)
    root = Node(sorted_nodes[0][0], sorted_nodes[0][1][0])
    for i, node in enumerate(sorted_nodes):
        if i==0:
            continue
        cur_node = root
        cnt = 1
        while True:
            if node[1][0] < cur_node.x:
                if cur_node.left:
                    cur_node = cur_node.left
                    continue
                else:
                    cur_node.left = Node(node[0], node[1][0])
                    break
            elif node[1][0] > cur_node.x:
                if cur_node.right:
                    cur_node = cur_node.right
                    continue
                else:
                    cur_node.right = Node(node[0], node[1][0])
                    break
            cnt += 1
            if cnt > 10:
                break
    answer = [[], []]
    forward_traversal(root, answer[0])
    backward_traversal(root, answer[1])
    return answer
