import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.math.BigInteger;

// Código criado para realizar o Problema Crivo de Eratostenes em Paralelismo de Dados

public class CrivoEratostenes extends Thread {

    private BigInteger inicio = BigInteger.ZERO, fim;
    private static int qtdPrimosTotal = 0;

    public CrivoEratostenes(BigInteger inicio, BigInteger fim) {
        this.inicio = inicio;
        this.fim = fim;
    }

    public void run() {
        List<Integer> primos = new ArrayList<>();
        List<Integer> primosIntervalo = crivoEratostenes(inicio.intValue(), fim.intValue());
        for (int i = 0; i < primosIntervalo.size(); i++) {
            int num = primosIntervalo.get(i);
            if (num > 1) {
                primos.add(num);
            }
        }
        synchronized (CrivoEratostenes.class) {
            qtdPrimosTotal += primos.size();
        }
        System.out.printf("Intervalo %d a %d: %s\n", inicio.intValue(), fim.intValue(), primos.toString());
    }

    public static void main(String[] args) throws InterruptedException {
        Scanner teclado = new Scanner(System.in);
        int numThreads;
        BigInteger posicao = BigInteger.ZERO;
        BigInteger tamanho = BigInteger.valueOf(10000);
        
        long tempo1, tempo2;

        System.out.println("Entre com a quantidade de threads: ");
        numThreads = teclado.nextInt();
        teclado.close();

        BigInteger tamanhoIntervalo = tamanho.divide(BigInteger.valueOf(numThreads));
        CrivoEratostenes[] threads = new CrivoEratostenes[numThreads];

        for (int j = 0; j < numThreads; j++) {
            threads[j] = new CrivoEratostenes(posicao, posicao.add(tamanhoIntervalo).subtract(BigInteger.ONE));
            posicao = posicao.add(tamanhoIntervalo);
        }

        tempo1 = System.currentTimeMillis();
        for (int j = 0; j < numThreads; j++) {
            threads[j].start();
        }

        for (int j = 0; j < numThreads; j++) {
            threads[j].join();
        }
        tempo2 = System.currentTimeMillis();

        System.out.println("\nQuantidade total de primos encontrados: " + qtdPrimosTotal);
        System.out.println("Tempo de execucao: " + (tempo2 - tempo1) + "ms");
    }

    private static List<Integer> crivoEratostenes(int inicio, int n) {
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
            if (primos[i] && i >= inicio) {
                primosList.add(i);
            }
        }

        return primosList;
    }

}
