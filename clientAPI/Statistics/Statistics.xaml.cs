﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Window
    {
        public Statistics()
        {
            InitializeComponent();
        }

       

        private void backClick(object sender, RoutedEventArgs e)
        {
            menu menu = new menu();
            menu.Show();
            this.Close();
        }

        private void ClickPersonal(object sender, RoutedEventArgs e)
        {
            Personal personal = new Personal();
            personal.Show();
            this.Close();
        }

        private void ClickScores(object sender, RoutedEventArgs e)
        {
            HighScores scores = new HighScores();
            scores.Show();
            this.Close();
        }
    }
}
