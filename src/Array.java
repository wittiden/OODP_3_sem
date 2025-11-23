import java.util.Random;
import java.util.Scanner;

public class Array {
    private String[] months;
    private double[] randomValues;

    public Array(){
        initializeMonths();
        initializeRandomValues();
    }

    private final void initializeMonths() {
        months = new String[] {
                "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
                "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь",
                "January", "February", "March", "April", "May", "June",
                "July", "August", "September", "October", "November", "December"
        };
    }
    private void initializeRandomValues() {
        randomValues = new double[12];
        Random random = new Random();
        for (int i = 0; i < randomValues.length; i++) {
            randomValues[i] = random.nextDouble() * 100;
        }
    }

    private double averageValue(){
        double result = 0;
        for(int i = 0; i < 12; i++){
            result += randomValues[i];
        }
        result /= randomValues.length;
        return result;
    }

    public void showLogic() {
        Scanner scanner = new Scanner(System.in);
        boolean choice_flag = false;
        do {
            System.out.println("\nВыберите язык / Choose language:");
            System.out.println("1 - Русский (Russian)");
            System.out.println("2 - English (Английский)");
            System.out.println("3 - Выйти / Exit: ");
            System.out.print("Ваш выбор / Your choice: ");
            int choice = scanner.nextInt();
            switch (choice) {
                case 1:
                    for (int i = 0; i < 12; i++) {
                        System.out.println("Месяц: " + months[i]);
                    }
                    System.out.println("Среднее значение: " + averageValue());
                    break;
                case 2:
                    for (int i = 12; i < 24; i++) {
                        System.out.println("Month: " + months[i]);
                    }
                    System.out.println("Average value: " + averageValue());
                    break;
                case 3:
                    choice_flag = true;
                    break;
                default:
                    System.out.println("Неверный выбор, попробуйте еще раз: ");
            }


        }while(!choice_flag);
    }
}
