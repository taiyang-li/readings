import java.util.ArrayList;
import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

import java.util.ArrayList;
import java.util.Scanner;

enum Color {
    RED, GREEN
}

abstract class Tree {

    private int value;
    private Color color;
    private int depth;

    public Tree(int value, Color color, int depth) {
        this.value = value;
        this.color = color;
        this.depth = depth;
    }

    public int getValue() {
        return value;
    }

    public Color getColor() {
        return color;
    }

    public int getDepth() {
        return depth;
    }

    public abstract void accept(TreeVis visitor);
}

class TreeNode extends Tree {

    private ArrayList<Tree> children = new ArrayList<>();

    public TreeNode(int value, Color color, int depth) {
        super(value, color, depth);
    }

    public void accept(TreeVis visitor) {
        visitor.visitNode(this);

        for (Tree child : children) {
            child.accept(visitor);
        }
    }

    public void addChild(Tree child) {
        children.add(child);
    }
}

class TreeLeaf extends Tree {

    public TreeLeaf(int value, Color color, int depth) {
        super(value, color, depth);
    }

    public void accept(TreeVis visitor) {
        visitor.visitLeaf(this);
    }
}

abstract class TreeVis
{
    public abstract int getResult();
    public abstract void visitNode(TreeNode node);
    public abstract void visitLeaf(TreeLeaf leaf);

}

class SumInLeavesVisitor extends TreeVis {
    public int getResult() {
        return sum_in_leaves;
    }

    public void visitNode(TreeNode node) {
    }

    public void visitLeaf(TreeLeaf leaf) {
        sum_in_leaves += leaf.getValue();
    }

    private int sum_in_leaves = 0;
}

class ProductOfRedNodesVisitor extends TreeVis {
    private long result = 1;
    private final int M = 1000000007;

    public int getResult() {
        return (int) result;
    }

    public void visitNode(TreeNode node) {
        if (node.getColor() == Color.RED) {
            result = (result * node.getValue()) % M;
        }
    }

    public void visitLeaf(TreeLeaf leaf) {
        if (leaf.getColor() == Color.RED) {
            result = (result * leaf.getValue()) % M;
        }
    }
}

class FancyVisitor extends TreeVis {
    public int getResult() {
        return Math.abs(sum_of_green_leaf_nodes - sum_of_non_leaf_even_nodes);
    }

    public void visitNode(TreeNode node) {
        if (node.getDepth() % 2 == 0) {
            sum_of_non_leaf_even_nodes += node.getValue();
        }
    }

    public void visitLeaf(TreeLeaf leaf) {
        if (leaf.getColor() == Color.GREEN) {
            sum_of_green_leaf_nodes += leaf.getValue();
        }
    }

    private int sum_of_non_leaf_even_nodes = 0;
    private int sum_of_green_leaf_nodes = 0;
}

public class Solution {

    /*
    public static Tree solve() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();

        // read values
        int[] values = new int[n];
        for (int i=0; i<n; ++i) {
            values[i] = in.nextInt();
        }

        // read colors
        Color[] colors = new Color[n];
        for (int i=0; i<n; ++i) {
            int tmp = in.nextInt();
            switch (tmp) {
                case 0:
                    colors[i] = Color.RED;
                    break;
                case 1:
                    colors[i] = Color.GREEN;
                    break;
            }
        }

        // read edges
        ArrayList<int[]> edges = new ArrayList<int[]>();
        while (in.hasNextInt()) {
            int x = in.nextInt();
            int y = in.nextInt();
            // System.out.printf("%d %d\n", x, y);
            edges.add(new int[]{x-1, y-1});
        }
        Collections.sort(edges, new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                if (o1[0] < o2[0])
                    return -1;
                else if (o1[0] == o2[0]) {
                    if (o1[1] < o2[1])
                        return -1;
                    else if (o1[1] == o2[1])
                        return 0;
                    else
                        return 1;
                }
                else
                    return 1;

            }
        });

        // calculate depths
        int[] depths = new int[n];
        int[] flags = new int[n];
        depths[0] = 0;
        for (int i=0; i<edges.size(); ++i) {
            int up = edges.get(i)[0];
            int down = edges.get(i)[1];
            depths[down] = depths[up] + 1;
            flags[up] = 1;
        }

        // build tree
        Tree[] nodes = new Tree[n];
        for (int i=0; i<n; ++i) {
            if (flags[i] == 1) {
                nodes[i] = new TreeNode(values[i], colors[i], depths[i]);
            } else {
                nodes[i] = new TreeLeaf(values[i], colors[i], depths[i]);
            }
        }
        for (int i=0; i<edges.size(); ++i) {
            int up = edges.get(i)[0];
            int down = edges.get(i)[1];
            TreeNode father = (TreeNode) nodes[up];
            father.addChild(nodes[down]);
        }
        in.close();
        return nodes[0];
    }
    */

        private static int [] values;
        private static Color [] colors;
        private static HashMap<Integer, HashSet<Integer>> map;

        public static Tree solve() {
            Scanner scan = new Scanner(System.in);
            int numNodes = scan.nextInt();

            /* Read and save nodes and colors */
            values = new int[numNodes];
            colors = new Color[numNodes];
            map = new HashMap<>(numNodes);
            for (int i = 0; i < numNodes; i++) {
                values[i] = scan.nextInt();
            }
            for (int i = 0; i < numNodes; i++) {
                colors[i] = scan.nextInt() == 0 ? Color.RED : Color.GREEN;
            }

            /* Save edges */
            for (int i = 0; i < numNodes - 1; i++) {
                int u = scan.nextInt();
                int v = scan.nextInt();

                /* Edges are undirected: Add 1st direction */
                HashSet<Integer> uNeighbors = map.get(u);
                if (uNeighbors == null) {
                    uNeighbors = new HashSet<>();
                    map.put(u, uNeighbors);
                }
                uNeighbors.add(v);

                /* Edges are undirected: Add 2nd direction */
                HashSet<Integer> vNeighbors = map.get(v);
                if (vNeighbors == null) {
                    vNeighbors = new HashSet<>();
                    map.put(v, vNeighbors);
                }
                vNeighbors.add(u);
            }
            scan.close();

            /* Handle 1-node tree */
            if (numNodes == 1) {
                return new TreeLeaf(values[0], colors[0], 0);
            }

            /* Create Tree */
            TreeNode root = new TreeNode(values[0], colors[0], 0);
            addChildren(root, 1);
            return root;
        }

        /* Recursively adds children of a TreeNode */
        private static void addChildren(TreeNode parent, Integer parentNum) {
            /* Get HashSet of children and loop through them */
            for (Integer treeNum : map.get(parentNum)) {
                map.get(treeNum).remove(parentNum); // removes the opposite arrow direction

                /* Add child */
                HashSet<Integer> grandChildren = map.get(treeNum);
                boolean childHasChild = (grandChildren != null && !grandChildren.isEmpty());
                Tree tree;
                if (childHasChild) {
                    tree = new TreeNode(values[treeNum - 1], colors[treeNum - 1], parent.getDepth() + 1);
                } else {
                    tree = new TreeLeaf(values[treeNum - 1], colors[treeNum - 1], parent.getDepth() + 1);
                }
                parent.addChild(tree);

                /* Recurse if necessary */
                if (tree instanceof TreeNode) {
                    addChildren((TreeNode) tree, treeNum);
                }
            }
        }

        public static void main(String[] args) {
            Tree root = solve();
            SumInLeavesVisitor vis1 = new SumInLeavesVisitor();
            ProductOfRedNodesVisitor vis2 = new ProductOfRedNodesVisitor();
            FancyVisitor vis3 = new FancyVisitor();

            root.accept(vis1);
            root.accept(vis2);
            root.accept(vis3);

            int res1 = vis1.getResult();
            int res2 = vis2.getResult();
            int res3 = vis3.getResult();

            System.out.println(res1);
            System.out.println(res2);
            System.out.println(res3);
        }
    }
