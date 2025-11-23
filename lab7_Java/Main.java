import java.util.*;

public class Main{
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();

        //1
        System.out.print("Введите имя: ");
        String name = scanner.nextLine();
        System.out.println("Ваше имя - "+name);

        //2
        System.out.println("\nАргументы в обратном порядке:");
        for(int i = args.length-1; i >= 0; i--){
            System.out.println("[" + i + "] " +args[i]);
        }

        //3
        System.out.println("\nВведите количество случайных чисел: ");
        int rndNum_count = scanner.nextInt();
        int[] rndNums = new int[rndNum_count];
        for(int i = 0; i < rndNums.length; i++){
             rndNums[i] = random.nextInt(100);
        }
        System.out.println("В столбик:");
        for(int i = 0; i < rndNums.length; i++){
            System.out.println(rndNums[i]);
        }
        System.out.println("В строку:");
        for(int i = 0; i < rndNums.length; i++){
            System.out.print(rndNums[i]+" ");
        }

        //4
        scanner.nextLine();
        System.out.print("\n\nПароль: "+args[4]);

        boolean password_flag = false;
        do {
            System.out.print("\nПовторите выведенный пароль: ");
            String copy_password = scanner.nextLine();
            if (copy_password.equals(args[4])) {
                System.out.println("Аккаунт создан");
                password_flag = true;
            } else {
                System.out.println("Пароли не совпадают, повторите попытку!");
            }
        }while(!password_flag);

        //5
        System.out.print("\n1 целое число: ");
        System.out.println(args[5]);
        System.out.print("2 целое число: ");
        System.out.println(args[6]);
        boolean flag = false;
        int num1 = Integer.parseInt(args[5]);
        int num2 = Integer.parseInt(args[6]);
        do{
            System.out.println("\nВведите номер действия: ");
            System.out.println("1 - сумма");
            System.out.println("2 - произведение");
            System.out.println("3 - выйти");
            int choice = scanner.nextInt();
            switch(choice){
                case 1:
                    System.out.println(num1+num2);
                    break;
                case 2:
                    System.out.println(num1*num2);
                    break;
                case 3:
                    flag = true;
                    break;
                default:
                    System.out.println("Неверный выбор!");
            }


        }while(!flag);

        //6
        ArrayList<Integer> arrayList = new ArrayList<>();
        boolean task6_flag = false;
        do{
            System.out.println("\nВведите номер действия: ");
            System.out.println("1 - Добавить целое число");
            System.out.println("2 - Показать четные");
            System.out.println("3 - Показать нечетные");
            System.out.println("4 - Показать max");
            System.out.println("5 - Показать min");
            System.out.println("6 - Показать те, что делятся на 3 или 9");
            System.out.println("7 - Сортировать пузырьком по убыванию");
            System.out.println("8 - выйти");
            int task6_choice = scanner.nextInt();

            switch(task6_choice){
                case 1:
                    System.out.println("Введите число: ");
                    int value = scanner.nextInt();
                    arrayList.add(value);
                    break;
                case 2:
                    if(arrayList.isEmpty()){
                        break;
                    }
                    System.out.println("Все\n"+arrayList);
                    System.out.println("Четные:");

                    for(int  i = 0; i < arrayList.size(); i++){
                        if(arrayList.get(i) % 2 == 0 ){
                            System.out.println(arrayList.get(i));
                        }
                    }
                    break;
                case 3:
                    if(arrayList.isEmpty()){
                        break;
                    }
                    System.out.println("Все\n"+arrayList);
                    System.out.println("Нечетные:");
                    for(int  i = 0; i < arrayList.size(); i++){
                        if(arrayList.get(i) % 2 != 0 ){
                            System.out.println(arrayList.get(i));
                        }
                    }
                    break;
                case 4:
                    if(arrayList.isEmpty()){
                        break;
                    }
                    System.out.println("Все\n"+arrayList);
                    System.out.println("max:");
                    int max = Collections.max(arrayList);
                    System.out.println(max);

                    break;
                case 5:
                    if(arrayList.isEmpty()){
                        break;
                    }
                    System.out.println("Все\n"+arrayList);
                    System.out.println("min:");
                    int min = Collections.min(arrayList);
                    System.out.println(min);


                    break;
                case 6:
                    if(arrayList.isEmpty()){
                        break;
                    }
                    System.out.println("Все\n"+arrayList);
                    System.out.println("Делятся на 3 или 9:");

                    for(int  i = 0; i < arrayList.size(); i++){
                        if(arrayList.get(i) % 3 == 0 || arrayList.get(i) % 9 == 0){
                            System.out.println(arrayList.get(i));
                        }
                    }
                    break;
                case 7:
                    if(arrayList.isEmpty()){
                        break;
                    }
                    System.out.println("Все\n"+arrayList);
                    System.out.println("Сортировка пузырьком по убыванию (ПО КОПИИ)");
                    ArrayList<Integer> newarrayList = new ArrayList<>(arrayList);
                    bubbleSortDescending(newarrayList);
                    System.out.println(newarrayList);

                    break;
                case 8:
                    task6_flag = true;
                    break;
                default:
                    System.out.println("Неверный выбор!");

            }
        }while(!task6_flag);

        Array arr = new Array();
        arr.showLogic();
    }
    public static void bubbleSortDescending(ArrayList<Integer> list) {
        int n = list.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (list.get(j) < list.get(j + 1)) {
                    int temp = list.get(j);
                    list.set(j, list.get(j + 1));
                    list.set(j + 1, temp);
                }
            }
        }

    }
}