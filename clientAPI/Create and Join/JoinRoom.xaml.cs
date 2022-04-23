using clientAPI.Requests;
using System;
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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        public JoinRoom()
        {
            InitializeComponent();
        }

        
        private void clickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu();
            menu.Show();
        }

        private void clickJoin(object sender, RoutedEventArgs e)
        {
            string id;
            if (roomsList.SelectedItem != null)
            {
                id = roomsList.SelectedItem.ToString();
                uint fixedId = Convert.ToUInt32(id);
                JoinRoomRequest joinRoomRequest = new JoinRoomRequest(fixedId);
            }
            else
            {
                MessageBox.Show("Selection Empty!");
            }
              
                    
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            
        }
    }
}
