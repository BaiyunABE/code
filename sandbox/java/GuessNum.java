import java.util.Random;
import java.util.Scanner;

public class GuessNum {
    public static void main(String[] args) {
        // 1. 创建随机数对象、键盘录入对象
        Random r = new Random();
        Scanner sc = new Scanner(System.in);

        // 2. 生成 1 ~ 100 随机数
        int target = r.nextInt(100) + 1;
        int count = 0; // 记录猜测次数

        System.out.println("===== 猜数字游戏开始 =====");
        System.out.println("系统已生成 1~100 之间的数字，请开始猜测：");

        // 3. 循环猜数字
        while (true) {
            System.out.print("请输入你猜的数字：");
            int num = sc.nextInt();
            count++;

            if (num > target) {
                System.out.println("猜大了，往小了猜！");
            } else if (num < target) {
                System.out.println("猜小了，往大了猜！");
            } else {
                // 猜对，跳出循环
                System.out.println("恭喜你，猜对啦！");
                System.out.println("一共猜测了 " + count + " 次");
                break;
            }
        }

        // 关闭输入流
        sc.close();
    }
}

