using System;
using System.Collections.Generic;
using System.IO;

namespace Lottery_Csharp_dotNet
{
    // List<int> numbers = new List<int>();
    // numbers.Count
    class Program
    {

        public const int LOTTERY_NUMBERS = 7;
        public const int ADDITIONAL_NUMBERS = 4;
        public const int MAX_NUMBER = 100;

        public class Lottery_Line
        {
            public string name;
            public int[] numbers;
            public int right;
            public int additional_number;
        };


        static void read_lottery_lines(List<Lottery_Line> players)
        {
            Console.WriteLine("Enter lottery lines:");
            while (true)
            {
                string line = Console.ReadLine();
                if (line.Length != 0)
                {
                    string[] lineSplited = line.Split(',');
                    //Console.WriteLine(line);
                    //Console.WriteLine(lineSplited[]);
                    if (lineSplited.Length != LOTTERY_NUMBERS + 1)
                    {
                        Console.WriteLine("Wrong entry: Renter lottery line");
                        continue;
                    }
                    Lottery_Line player = new Lottery_Line();
                    player.numbers = new int[LOTTERY_NUMBERS];
                    for (int i = 0; i < lineSplited.Length; i++)
                    {
                        //Console.WriteLine(lineSplited[i]);
                        if (i == 0)
                        {
                            player.name = lineSplited[i];
                        }
                        else
                        {
                            player.numbers[i - 1] = Convert.ToInt32(lineSplited[i]);
                        }
                    }
                    players.Add(player);
                }
                else
                {
                    break;
                }
            };
        }
        static void correct_line_generate(int[] correct_line, int[] additional_line)
        {
            Random rnd = new Random();
            for (int i = 0; i < LOTTERY_NUMBERS; i++)
            {
                int number = rnd.Next(1, MAX_NUMBER); // creates a number between 1 and 100.
                correct_line[i] = number;
            }
            for (int i = 0; i < ADDITIONAL_NUMBERS; i++)
            {
                int number = rnd.Next(1, MAX_NUMBER); // creates a number between 1 and 100.
                additional_line[i] = number;
            }
            int month = rnd.Next(1, 100); // creates a number between 1 and 100.

        }
        static void sort_data(List<Lottery_Line> players, int[] correct_line, int[] additional_line)
        {
            for (int i = 0; i < players.Count; i++)
            {
                Array.Sort(players[i].numbers);
            }
            Array.Sort(correct_line);
            Array.Sort(additional_line);

        }
        static void correct_data(List<Lottery_Line> players, int[] correct_line, int[] additional_line)
        {
            for (int i = 0; i < players.Count; i++)
            {
                int right = 0;
                int additional = 0;

                for (int j = 0; j < correct_line.Length; j++)
                {
                    if (Array.BinarySearch(players[i].numbers, correct_line[j]) >= 0)
                    {
                        right++;
                    }
                }

                for (int j = 0; j < additional_line.Length; j++)
                {
                    if (Array.BinarySearch(players[i].numbers, additional_line[j]) >= 0)
                    {
                        additional++;
                    }
                }
                players[i].right = right;
                players[i].additional_number = additional;
            }
        }
        static void print_data(List<Lottery_Line> players, int[] correct_line, int[] additional_line)
        {
            Console.WriteLine($"Correct row {correct_line[0]}, {correct_line[1]}, {correct_line[2]}," +
                $" {correct_line[3]}, {correct_line[4]}, {correct_line[5]}, {correct_line[6]}");

            Console.WriteLine($"{additional_line[0]}, {additional_line[1]}, {additional_line[2]}, " +
                $"{additional_line[2]},");

            foreach (Lottery_Line player in players)
            {
                Console.Write($"{player.name}, {player.numbers[0]}, { player.numbers[1]}, {player.numbers[2]}, " +
                    $"{player.numbers[3]}, {player.numbers[4]}, {player.numbers[5]}, {player.numbers[6]}");
                if (player.right != 0)
                {
                    Console.Write($" {player.right} right");
                }
                else
                {
                    Console.Write(" zero right");
                }

                if (player.additional_number != 0)
                {
                    Console.WriteLine($" {player.additional_number}");
                }
                else
                {
                    Console.WriteLine(" zero");
                }

                //Console.WriteLine();
                Console.WriteLine("additional number");
            }
        }
        static void store_data(List<Lottery_Line> players, int[] correct_line, int[] additional_line)
        {

            // Set a variable to the Documents path.
            string docPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            string[] lines = { $"Correct row {correct_line[0]}, {correct_line[1]}, {correct_line[2]}," +
                $" {correct_line[3]}, {correct_line[4]}, {correct_line[5]}, {correct_line[6]}",
                $"{additional_line[0]}, {additional_line[1]}, {additional_line[2]}, " +
                $"{additional_line[2]}," };

            string text = lines[0] + Environment.NewLine;
            // Write the text to a new file named "WriteFile.txt"
            File.WriteAllText(Path.Combine(docPath, "Result.txt"), text);
            text = lines[1] + Environment.NewLine;
            // Append new lines of text to the file
            File.AppendAllText(Path.Combine(docPath, "Result.txt"), text);

            foreach (Lottery_Line player in players)
            {
                string line = $"{player.name}, {player.numbers[0]}, { player.numbers[1]}, {player.numbers[2]}, " +
                    $"{player.numbers[3]}, {player.numbers[4]}, {player.numbers[5]}, {player.numbers[6]}";
                if (player.right != 0)
                {
                    line += $" {player.right} right";
                }
                else
                {
                    line += " zero right";
                }

                if (player.additional_number != 0)
                {
                    line += $" {player.additional_number}" + Environment.NewLine;
                }
                else
                {
                    line += " zero" + Environment.NewLine;
                }
                File.AppendAllText(Path.Combine(docPath, "Result.txt"), line);
                File.AppendAllText(Path.Combine(docPath, "Result.txt"), "additional number" + Environment.NewLine);
            }
        }

            static void Main(string[] args)
            {
                List<Lottery_Line> players = new List<Lottery_Line>();
                int[] correct_line = new int[LOTTERY_NUMBERS];
                int[] additional_line = new int[ADDITIONAL_NUMBERS];

                read_lottery_lines(players);
                correct_line_generate(correct_line, additional_line);
                sort_data(players, correct_line, additional_line);
                correct_data(players, correct_line, additional_line);
                print_data(players, correct_line, additional_line);
                store_data(players, correct_line, additional_line);

            }
        }
    }
