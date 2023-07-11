import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

// Código criado para realizar o Problema Crivo de Eratostenes em Paralelismo de Controle

public class CrivoEratostenesControle extends Thread {

    private BigInteger tamanho;
    private static List<Integer> primosTotal = new ArrayList<>();

    public CrivoEratostenesControle(BigInteger tamanho) {
        this.tamanho = tamanho;
    }

    public void run() {
        List<Integer> primosIntervalo = crivoEratostenesControle(tamanho.intValue());
        synchronized (CrivoEratostenesControle.class) {
            for (Integer primo : primosIntervalo) {
                if (!primosTotal.contains(primo)) {
                    primosTotal.add(primo);
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Scanner teclado = new Scanner(System.in);
        int numThreads;
        BigInteger tamanho = BigInteger.valueOf(10000);
        long tempo1, tempo2;

        System.out.println("Entre com a quantidade de threads: ");
        numThreads = teclado.nextInt();
        teclado.close();

        CrivoEratostenesControle[] threads = new CrivoEratostenesControle[numThreads];

        for(int i = 0; i < numThreads; i++) {
            threads[i] = new CrivoEratostenesControle(tamanho);
        }

        tempo1 = System.currentTimeMillis();
        for (int j = 0; j < numThreads; j++) {
            threads[j].start();
        }

        for (int j = 0; j < numThreads; j++) {
            threads[j].join();
        }
        tempo2 = System.currentTimeMillis();


        System.out.println("\nNúmeros primos encontrados: ");
        for (Integer primo : primosTotal) {
            System.out.print(primo + " ");
        }
        System.out.println("\nQuantidade total de primos encontrados: " + primosTotal.size());
        System.out.println("Tempo de execucao: " + (tempo2 - tempo1) + "ms");
    }

    private static List<Integer> crivoEratostenesControle(int n) {
        boolean[] primos = new boolean[n + 1];
        List<Integer> primosList = new ArrayList<>();

        for (int i = 2; i <= n; i++)
            primos[i] = true;

        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (primos[i]) {
                for (int j = i; j * i <= n; j++) {
                    primos[i * j] = false;
                }
            }
        }

        for (int i = 2; i <= n; i++) {
            if (primos[i] == true) {
                primosList.add(i);
            }
        }

        return primosList;
    }

}
